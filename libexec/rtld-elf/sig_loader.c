#include <sys/types.h>
#include <sys/mman.h>
#include <machine/riscvreg.h>
#include <stdint.h>
#include <string.h>

#include "sig_loader.h"
#include "sig_debug.h"

static void** init_sig_got_pool(uint64_t sig_ptr_id_count) {
    size_t pool_size, page_num;

    // Calculate required pages
    pool_size = (sig_ptr_id_count + 1) * sizeof(void*);  /* +1 for dummy ID 0xffffff */
    page_num = (pool_size + 4095) / 4096;

    // Allocate using mmap
    void **sig_got_pool = (void**)mmap(NULL, page_num * 4096,
                                 PROT_READ | PROT_WRITE,
                                 MAP_PRIVATE | MAP_ANON, -1, 0);

    if (sig_got_pool == MAP_FAILED) return NULL;
    sig_got_pool = (void**)(xsig_setnewid(0) + (uint64_t)(sig_got_pool));

    SIG_DEBUG(
        debug_str("begin init_sig_got_pool: "); 
        debug_ptr(sig_got_pool);
        debug_str(", count = ");
        debug_int(sig_ptr_id_count);
        debug_str("\n");
    );

    sig_got_pool[0] = (void*)0;
    for (uint64_t i = 1; i <= sig_ptr_id_count; i++) {
        sig_got_pool[i] = xsig_setnewid(0);
        SIG_DEBUG(
            debug_str("init sig_got_pool entry ");
            debug_int(i);
            debug_str(": ");
            debug_ptr(sig_got_pool[i]);
            debug_str("\n");
        );
    }

    SIG_DEBUG(
        debug_str("init_sig_got_pool completed, count = ");
        debug_int(sig_ptr_id_count);
        debug_str("\n");
    );

    return sig_got_pool;
}

static void free_sig_got_pool(void** sig_got_pool, uint64_t sig_ptr_id_count) {
    size_t pool_size, page_num;
    if (sig_got_pool == NULL) return;

    // Clear entries
    for (uint64_t i = 0; i <= sig_ptr_id_count; i++) {
        sig_got_pool[i] = 0;
    }

    // Calculate size and unmap
    pool_size = (sig_ptr_id_count + 1) * sizeof(void*);
    page_num = (pool_size + 4095) / 4096;
    munmap(sig_got_pool, page_num * 4096);
}

static void init_got_array_first_stage(void* __raw * raw_got_array, uint64_t got_count, void** got_page_start_out, size_t* got_page_size_out) {
    // void** pc;
    size_t got_size, got_page_size;
    void* got_page_start;

    // Calculate GOT size and page-aligned region
    got_size = got_count * sizeof(void*);
    got_page_start = (void*)((uint64_t)raw_got_array & ~0xFFFUL);  // Page align down
    got_page_size = (((uint64_t)raw_got_array + got_size + 0xFFF) & ~0xFFFUL) - (uint64_t)got_page_start;

    // Save GOT region info for later restore
    *got_page_start_out = got_page_start;
    *got_page_size_out = got_page_size;

    // Temporarily make GOT writable (in case RELRO made it read-only)
    if (mprotect(got_page_start, got_page_size, PROT_READ | PROT_WRITE) != 0) {
        SIG_DEBUG(
            debug_str("WARNING: mprotect failed\n");
        );
    }

    // /* Get PC ID */
    // __asm__ __volatile__ (
    //     "auipc %0, 0\n"
    //     : "=r"(pc)
    // );
    // void** got_array = (void**)xsig_moveid(raw_got_array, pc);

    // for (uint64_t i = 1; i < got_count; i++) {
    //     got_array[i] = (void*)0 + (uint64_t)(raw_got_array[i]);
    //     SIG_DEBUG(
    //         debug_int(i);
    //         debug_chr(' ');
    //         debug_ptr(got_array[i]);
    //         debug_chr('\n');
    //     );
    // }
    // pc = 0;
    // got_array = 0;
}

// static void init_got_array_dummy(void* __raw * raw_got_array, uint64_t got_count, void** sig_got_pool) {
//     SIG_DEBUG(
//         debug_str("begin init_got_array_dummy, counter = ");
//         debug_int(0);
//         debug_str("\n");
//     );

//     void** pc;
//     __asm__ __volatile__ (
//         "auipc %0, 0\n"
//         : "=r"(pc)
//     );
//     void** got_array = (void**)xsig_moveid(raw_got_array, pc);
//     SIG_DEBUG(
//         debug_str("init got_array: ");
//         debug_ptr(got_array);
//         debug_str("\n");
//     );

//     for (uint64_t i = 1; i < got_count; i++) {
//         got_array[i] = sig_got_pool[0] + (uint64_t)(got_array[i]);
//         SIG_DEBUG(
//             debug_str("init got_array entry ");
//             debug_int(i);
//             debug_str(": ");
//             debug_ptr(got_array[i]);
//             debug_str("\n");
//         );
//     }
//     pc = 0;
//     got_array = 0;
// }

static void init_got_array(void* __raw * raw_got_array, uint64_t got_count,
                           __raw sig_got_table_entry* sig_got_table,
                           uint32_t sig_got_count, void** sig_got_pool) {
    SIG_DEBUG(
        debug_str("begin init_got_array, counter = ");
        debug_int(sig_got_count);
        debug_str("\n");
    );

    void** pc;
    __asm__ __volatile__ (
        "auipc %0, 0\n"
        : "=r"(pc)
    );
    void** got_array = (void**)((void*)pc - (uint64_t)xsig_setrawid(pc) + (uint64_t)raw_got_array);
    SIG_DEBUG(
        debug_str("init got_array: ");
        debug_ptr(got_array);
        debug_str("\n");
    );

    uint64_t sig_got_table_index = 0;
    uint64_t pointee_id, got_offset;
    if (sig_got_count > 0) {
        pointee_id = sig_got_table[0].pointee_id;
        got_offset = sig_got_table[0].got_offset;
    } else {
        pointee_id = 0;
        got_offset = 0;
    }

    for (uint64_t i = 1; i < got_count; i++) {
        if (got_offset == i && sig_got_table_index < sig_got_count) {
            SIG_DEBUG(
                debug_str("sig_got entry index: ");
                debug_int(sig_got_table_index);
                debug_str(" pointee_id: ");
                debug_int(pointee_id);
                debug_str(" got_offset: ");
                debug_int(got_offset);
                debug_str("\n");
            );
            // Use sig_got_table entry
            got_array[i] = sig_got_pool[pointee_id] + (uint64_t)(raw_got_array[i]);
            sig_got_table_index++;
            if (sig_got_table_index < sig_got_count) {
                pointee_id = sig_got_table[sig_got_table_index].pointee_id;
                got_offset = sig_got_table[sig_got_table_index].got_offset;
            } else {
                pointee_id = 0;
                got_offset = 0;
            }
            SIG_DEBUG(
                debug_str("init got_array entry ");
                debug_int(i);
                debug_str(": ");
                debug_ptr(got_array[i]);
                debug_str("\n");
            );
        }
    }
    pc = 0;
    got_array = 0;
}

inline static void* get_idptr(void** sig_got_pool, uint32_t id) {
    if (id == SIG_EXTERNAL_ID) {
        return sig_got_pool[0];
    } else if (id == SIG_NULL_ID) {
        return 0;
    } else {
        return sig_got_pool[id];
    }
}

inline static void init_one_global_ptr(uint64_t addr, uint32_t data_id,
                                       uint32_t pointee_id, void** sig_got_pool) {
    void** data_pointer = (void**)(get_idptr(sig_got_pool, data_id) + addr);
    void* pointee_pointer = get_idptr(sig_got_pool, pointee_id) + *((__raw uint64_t*)addr);
    *data_pointer = pointee_pointer;
    SIG_DEBUG(
        debug_str("  addr: ");
        debug_ptr(data_pointer);
        debug_str(" data: ");
        debug_ptr(*data_pointer);
        debug_str("\n");
    );
}
    
static void init_sig_ptr_single(__raw sig_ptr_header_single_entry* sig_ptr_header_single,
                                uint32_t sig_ptr_header_single_count, void** sig_got_pool) {
    SIG_DEBUG(
        debug_str("begin init_sig_ptr_single, counter = ");
        debug_int(sig_ptr_header_single_count);
        debug_str("\n");
    );
    uint64_t addr;
    uint32_t data_id;
    uint32_t pointee_id;
    for (uint32_t i = 0; i < sig_ptr_header_single_count; i++) {
        addr = sig_ptr_header_single[i].addr;
        data_id = sig_ptr_header_single[i].data_id;
        pointee_id = sig_ptr_header_single[i].pointee_id;
        init_one_global_ptr(addr, data_id, pointee_id, sig_got_pool);
    }
}

static void init_sig_ptr_contig_same(__raw sig_ptr_header_contig_same_entry* sig_ptr_header_contig_same,
                                     uint32_t sig_ptr_header_contig_same_count, void** sig_got_pool) {
    SIG_DEBUG(
        debug_str("begin init_sig_ptr_contig_same, counter = ");
        debug_int(sig_ptr_header_contig_same_count);
        debug_str("\n");
    );
    uint64_t addr;
    uint64_t length;
    uint32_t data_id;
    uint32_t pointee_id;
    for (uint32_t i = 0; i < sig_ptr_header_contig_same_count; i++) {
        addr = sig_ptr_header_contig_same[i].addr;
        length = sig_ptr_header_contig_same[i].length;
        data_id = sig_ptr_header_contig_same[i].data_id;
        pointee_id = sig_ptr_header_contig_same[i].pointee_id;
        for (uint64_t offset = 0; offset < length; offset++) {
            init_one_global_ptr(addr + offset * 8, data_id, pointee_id, sig_got_pool);
        }
    }
}

static void init_sig_ptr_contig_diff(__raw sig_ptr_header_contig_diff_entry* sig_ptr_header_contig_diff,
                                     __raw sig_id_contig_diff_entry* sig_id_contig_diff,
                                     uint32_t sig_ptr_header_contig_diff_count, void** sig_got_pool) {
    SIG_DEBUG(
        debug_str("begin init_sig_ptr_contig_diff, counter = ");
        debug_int(sig_ptr_header_contig_diff_count);
        debug_str("\n");
    );
    uint64_t addr;
    uint64_t length;
    uint32_t data_id;
    uint32_t pointee_id;
    uint64_t sig_id_index = 0;
    for (uint32_t i = 0; i < sig_ptr_header_contig_diff_count; i++) {
        addr = sig_ptr_header_contig_diff[i].addr;
        length = sig_ptr_header_contig_diff[i].length;
        data_id = sig_id_contig_diff[sig_id_index++];

        for (uint64_t offset = 0; offset < length; offset++) {
            pointee_id = sig_id_contig_diff[sig_id_index++];
            init_one_global_ptr(addr + offset * 8, data_id, pointee_id, sig_got_pool);
        }
    }
}

static void init_sig_ptr_sparse_same(__raw sig_ptr_header_sparse_same_entry* sig_ptr_header_sparse_same,
                                     __raw sig_offset_sparse_same_entry* sig_offset_sparse_same,
                                     uint32_t sig_ptr_header_sparse_same_count, void** sig_got_pool) {
    SIG_DEBUG(
        debug_str("begin init_sig_ptr_sparse_same, counter = ");
        debug_int(sig_ptr_header_sparse_same_count);
        debug_str("\n");
    );
    uint64_t addr;
    uint64_t length;
    uint32_t data_id;
    uint32_t pointee_id;
    uint64_t offset;
    uint64_t sig_offset_index = 0;
    for (uint32_t i = 0; i < sig_ptr_header_sparse_same_count; i++) {
        addr = sig_ptr_header_sparse_same[i].addr;
        length = sig_ptr_header_sparse_same[i].length;
        data_id = sig_ptr_header_sparse_same[i].data_id;
        pointee_id = sig_ptr_header_sparse_same[i].pointee_id;
        for (uint64_t index = 0; index < length; index++) {
            offset = sig_offset_sparse_same[sig_offset_index++];
            init_one_global_ptr(addr + offset, data_id, pointee_id, sig_got_pool);
        }
    }
}

static void init_sig_ptr_sparse_diff(__raw sig_ptr_header_sparse_diff_entry* sig_ptr_header_sparse_diff,
                                     __raw sig_id_sparse_diff_entry* sig_id_sparse_diff,
                                     __raw sig_offset_sparse_diff_entry* sig_offset_sparse_diff,
                                     uint32_t sig_ptr_header_sparse_diff_count, void** sig_got_pool) {
    SIG_DEBUG(
        debug_str("begin init_sig_ptr_sparse_diff, counter = ");
        debug_int(sig_ptr_header_sparse_diff_count);
        debug_str("\n");
    );
    uint64_t addr;
    uint64_t length;
    uint32_t data_id;
    uint32_t pointee_id;
    uint64_t offset;
    uint64_t sig_id_index = 0;
    uint64_t sig_offset_index = 0;
    for (uint32_t i = 0; i < sig_ptr_header_sparse_diff_count; i++) {
        addr = sig_ptr_header_sparse_diff[i].addr;
        length = sig_ptr_header_sparse_diff[i].length;
        data_id = sig_id_sparse_diff[sig_id_index++];
        for (uint64_t index = 0; index < length; index++) {
            offset = sig_offset_sparse_diff[sig_offset_index++];
            pointee_id = sig_id_sparse_diff[sig_id_index++];
            init_one_global_ptr(addr + offset, data_id, pointee_id, sig_got_pool);
        }
    }
}

#define getsection(sig_header, section_name) ((__raw uint8_t *)(sig_header) + (sig_header)->section_name##_offset)

void global_init(__raw sig_header* sig_header_struct) {
    __raw sig_got_table_entry* sig_got_section;
    __raw sig_ptr_header_single_entry* sig_ptr_header_single_section;
    __raw sig_ptr_header_contig_same_entry* sig_ptr_header_contig_same_section;
    __raw sig_ptr_header_contig_diff_entry* sig_ptr_header_contig_diff_section;
    __raw sig_id_contig_diff_entry* sig_id_contig_diff_section;
    __raw sig_ptr_header_sparse_same_entry* sig_ptr_header_sparse_same_section;
    __raw sig_offset_sparse_same_entry* sig_offset_sparse_same_section;
    __raw sig_ptr_header_sparse_diff_entry* sig_ptr_header_sparse_diff_section;
    __raw sig_id_sparse_diff_entry* sig_id_sparse_diff_section;
    __raw sig_offset_sparse_diff_entry* sig_offset_sparse_diff_section;
    void* got_page_start;
    size_t got_page_size;

    SIG_DEBUG(
        debug_str("\n========== global_init START ==========\n");
        debug_str("sig_header: ");
        debug_ptr(sig_header_struct);
        debug_str("\n");
        debug_str("sig_ptr_id_count: ");
        debug_int(sig_header_struct->sig_ptr_id_count);
        debug_str("\n");
        debug_str("sig_ptr_header_single_count: ");
        debug_int(sig_header_struct->sig_ptr_header_single_count);
        debug_str("\n");
        debug_str("sig_ptr_header_contig_same_count: ");
        debug_int(sig_header_struct->sig_ptr_header_contig_same_count);
        debug_str("\n");
        debug_str("sig_ptr_header_contig_diff_count: ");
        debug_int(sig_header_struct->sig_ptr_header_contig_diff_count);
        debug_str("\n");
        debug_str("sig_ptr_header_sparse_same_count: ");
        debug_int(sig_header_struct->sig_ptr_header_sparse_same_count);
        debug_str("\n");
        debug_str("sig_ptr_header_sparse_diff_count: ");
        debug_int(sig_header_struct->sig_ptr_header_sparse_diff_count);
        debug_str("\n");
        debug_str("sig_got_count: ");
        debug_int(sig_header_struct->sig_got_count);
        debug_str("\n");
        debug_str("got_count: ");
        debug_int(sig_header_struct->got_count);
        debug_str("\n\n");
    );

    void* __raw * got_section = (void* __raw *)getsection(sig_header_struct, got);
    init_got_array_first_stage(got_section, sig_header_struct->got_count, &got_page_start, &got_page_size);
    
    void** sig_got_pool = init_sig_got_pool(sig_header_struct->sig_ptr_id_count);
    if (sig_got_pool == NULL) return;

    sig_got_section = (__raw sig_got_table_entry*)getsection(sig_header_struct, sig_got);
    if (sig_header_struct->sig_got_count != 0) {
        init_got_array(got_section, sig_header_struct->got_count, sig_got_section,
                       sig_header_struct->sig_got_count, sig_got_pool);
    }

    if (sig_header_struct->sig_ptr_header_single_count > 0) {
        sig_ptr_header_single_section =
            (__raw sig_ptr_header_single_entry*)getsection(sig_header_struct, sig_ptr_header_single);
        init_sig_ptr_single(sig_ptr_header_single_section,
                           sig_header_struct->sig_ptr_header_single_count, sig_got_pool);
    }

    if (sig_header_struct->sig_ptr_header_contig_same_count > 0) {
        sig_ptr_header_contig_same_section =
            (__raw sig_ptr_header_contig_same_entry*)getsection(sig_header_struct, sig_ptr_header_contig_same);
        init_sig_ptr_contig_same(sig_ptr_header_contig_same_section,
                                sig_header_struct->sig_ptr_header_contig_same_count, sig_got_pool);
    }

    if (sig_header_struct->sig_ptr_header_contig_diff_count > 0) {
        sig_ptr_header_contig_diff_section =
            (__raw sig_ptr_header_contig_diff_entry*)getsection(sig_header_struct, sig_ptr_header_contig_diff);
        sig_id_contig_diff_section =
            (__raw sig_id_contig_diff_entry*)getsection(sig_header_struct, sig_id_contig_diff);
        init_sig_ptr_contig_diff(sig_ptr_header_contig_diff_section, sig_id_contig_diff_section,
                                sig_header_struct->sig_ptr_header_contig_diff_count, sig_got_pool);
    }

    if (sig_header_struct->sig_ptr_header_sparse_same_count > 0) {
        sig_ptr_header_sparse_same_section =
            (__raw sig_ptr_header_sparse_same_entry*)getsection(sig_header_struct, sig_ptr_header_sparse_same);
        sig_offset_sparse_same_section =
            (__raw sig_offset_sparse_same_entry*)getsection(sig_header_struct, sig_offset_sparse_same);
        init_sig_ptr_sparse_same(sig_ptr_header_sparse_same_section, sig_offset_sparse_same_section,
                                sig_header_struct->sig_ptr_header_sparse_same_count, sig_got_pool);
    }

    if (sig_header_struct->sig_ptr_header_sparse_diff_count > 0) {
        sig_ptr_header_sparse_diff_section =
            (__raw sig_ptr_header_sparse_diff_entry*)getsection(sig_header_struct, sig_ptr_header_sparse_diff);
        sig_id_sparse_diff_section =
            (__raw sig_id_sparse_diff_entry*)getsection(sig_header_struct, sig_id_sparse_diff);
        sig_offset_sparse_diff_section =
            (__raw sig_offset_sparse_diff_entry*)getsection(sig_header_struct, sig_offset_sparse_diff);
        init_sig_ptr_sparse_diff(sig_ptr_header_sparse_diff_section, sig_id_sparse_diff_section,
                                sig_offset_sparse_diff_section,
                                sig_header_struct->sig_ptr_header_sparse_diff_count, sig_got_pool);
    }

    free_sig_got_pool(sig_got_pool, sig_header_struct->sig_ptr_id_count);

    // Restore GOT to read-only (RELRO protection)
    if (mprotect(got_page_start, got_page_size, PROT_READ) != 0) {
        SIG_DEBUG(
            debug_str("WARNING: mprotect restore failed\n");
        );
    }

    SIG_DEBUG(
        debug_str("========== global_init COMPLETED ==========\n\n");
    );
}

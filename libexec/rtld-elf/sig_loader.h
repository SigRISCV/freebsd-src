#ifndef __SIG_LOADER_H__
#define __SIG_LOADER_H__

#include <stdint.h>

typedef struct {
    uint64_t got_offset;
    uint64_t pointee_id;
} sig_got_table_entry;

/*
 * sig_header structure
 * This is the main header section that contains all metadata and offsets
 * for SigRISCV pointer initialization.
 *
 * Layout (152 bytes total):
 *   - 7 x uint64_t counters (56 bytes)
 *   - 10 x int64_t segment offsets (80 bytes) - relative to sig_header base
 *   - 1 x int64_t .got section offset (8 bytes)
 *   - 1 x uint64_t .got entry count (8 bytes)
 */
typedef struct {
    // Counters for various pointer categories (56 bytes)
    uint64_t sig_ptr_id_count;                  // Total number of unique IDs
    uint64_t sig_ptr_header_single_count;       // Count of single pointers
    uint64_t sig_ptr_header_contig_same_count;  // Count of contiguous same ID arrays
    uint64_t sig_ptr_header_contig_diff_count;  // Count of contiguous diff ID arrays
    uint64_t sig_ptr_header_sparse_same_count;  // Count of sparse same ID arrays
    uint64_t sig_ptr_header_sparse_diff_count;  // Count of sparse diff ID arrays
    uint64_t sig_got_count;                     // Count of sig_got entries

    // Segment offsets (80 bytes) - relative to this sig_header's address
    uint64_t sig_ptr_header_single_offset;
    uint64_t sig_ptr_header_contig_same_offset;
    uint64_t sig_ptr_header_contig_diff_offset;
    uint64_t sig_ptr_header_sparse_same_offset;
    uint64_t sig_ptr_header_sparse_diff_offset;
    uint64_t sig_offset_sparse_same_offset;
    uint64_t sig_offset_sparse_diff_offset;
    uint64_t sig_id_contig_diff_offset;
    uint64_t sig_id_sparse_diff_offset;
    uint64_t sig_got_offset;

    // GOT section info (16 bytes)
    uint64_t got_offset;      // Offset to .got section
    uint64_t got_count;       // Number of .got entries
} sig_header;

typedef struct {
    uint64_t addr;
    uint32_t data_id;
    uint32_t pointee_id;
} sig_ptr_header_single_entry;

typedef struct {
    uint64_t addr;
    uint64_t length;
    uint32_t data_id;
    uint32_t pointee_id;
} sig_ptr_header_contig_same_entry;

typedef struct {
    uint64_t addr;
    uint64_t length;
} sig_ptr_header_contig_diff_entry;

typedef uint32_t sig_id_contig_diff_entry;

typedef sig_ptr_header_contig_same_entry sig_ptr_header_sparse_same_entry;
typedef uint64_t sig_offset_sparse_same_entry;

typedef sig_ptr_header_contig_diff_entry sig_ptr_header_sparse_diff_entry;
typedef sig_id_contig_diff_entry sig_id_sparse_diff_entry;
typedef uint64_t sig_offset_sparse_diff_entry;

#define SIG_EXTERNAL_ID  0xFFFFFF
#define SIG_NULL_ID      0

void global_init(__raw sig_header* sig_header_struct, void* __raw* raw_sig_got_pool);

#endif /* __SIG_LOADER_H__ */

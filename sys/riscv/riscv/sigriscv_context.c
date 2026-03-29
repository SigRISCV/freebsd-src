#include <sys/sigriscv_context.h>

#ifdef SIGRISCV

#define CSR_GPRID_BASE		0x5d0
#define CSR_PCID			0x5f2
#define CSR_IDCSR			0x5f3
#define CSR_ENCMAP          0x5f4
#define CSR_EXITRAW         0x5f5
#define CSR_HASHSIG         0x5f6

#define IDCSR_COUNTER_MASK  0x00ffffffu  /* ID counter: bits [23:0] */
#define IDCSR_USE           0x40000000u  /* SIG enable bit: bit 30 */
#define IDCSR_UPSE          0x80000000u  /* SIG previous enable bit: bit 31 */


#define csr_read(csr) \
    ({ \
        unsigned long _v; \
        __asm__ __volatile__("csrr %0, %1" : "=r"(_v) : "i"(csr)); \
        _v; \
    })

#define csr_write(csr, val) \
    do{\
        unsigned long _v = val; \
        __asm__ __volatile__("csrw %0, %1" : : "i"(csr), "r"(val) : "memory"); \
    }while(0)

#define READ_GPRID(idx) \
    do{\
        sc->gpr_id[idx] = (uint32_t)csr_read(CSR_GPRID_BASE + idx); \
    } while(0)

void get_sigriscv_context(sigriscv_context_t *sc){
    
	READ_GPRID(0);  READ_GPRID(1);  READ_GPRID(2);  READ_GPRID(3);
	READ_GPRID(4);  READ_GPRID(5);  READ_GPRID(6);  READ_GPRID(7);
	READ_GPRID(8);  READ_GPRID(9);  READ_GPRID(10); READ_GPRID(11);
	READ_GPRID(12); READ_GPRID(13); READ_GPRID(14); READ_GPRID(15);
	READ_GPRID(16); READ_GPRID(17); READ_GPRID(18); READ_GPRID(19);
	READ_GPRID(20); READ_GPRID(21); READ_GPRID(22); READ_GPRID(23);
	READ_GPRID(24); READ_GPRID(25); READ_GPRID(26); READ_GPRID(27);
	READ_GPRID(28); READ_GPRID(29); READ_GPRID(30); READ_GPRID(31);
	
    sc->pc_id = (uint32_t)csr_read(CSR_PCID);
    sc->idcsr = (uint32_t)csr_read(CSR_IDCSR);
    sc->encmap = csr_read(CSR_ENCMAP);
    sc->exitraw = csr_read(CSR_EXITRAW);
    sc->hashsig = csr_read(CSR_HASHSIG);
}

#define WRITE_GPRID(idx) \
    do{\
        csr_write(CSR_GPRID_BASE + idx, (unsigned long)sc->gpr_id[idx]); \
    } while(0)

int set_sigriscv_context(sigriscv_context_t *sc){

    WRITE_GPRID(0);  WRITE_GPRID(1);  WRITE_GPRID(2);  WRITE_GPRID(3);
	WRITE_GPRID(4);  WRITE_GPRID(5);  WRITE_GPRID(6);  WRITE_GPRID(7);
	WRITE_GPRID(8);  WRITE_GPRID(9);  WRITE_GPRID(10); WRITE_GPRID(11);
	WRITE_GPRID(12); WRITE_GPRID(13); WRITE_GPRID(14); WRITE_GPRID(15);
	WRITE_GPRID(16); WRITE_GPRID(17); WRITE_GPRID(18); WRITE_GPRID(19);
	WRITE_GPRID(20); WRITE_GPRID(21); WRITE_GPRID(22); WRITE_GPRID(23);
	WRITE_GPRID(24); WRITE_GPRID(25); WRITE_GPRID(26); WRITE_GPRID(27);
	WRITE_GPRID(28); WRITE_GPRID(29); WRITE_GPRID(30); WRITE_GPRID(31);
	
    csr_write(CSR_PCID, (unsigned long)sc->pc_id);
    csr_write(CSR_IDCSR, (unsigned long)sc->idcsr);
    csr_write(CSR_ENCMAP, sc->encmap);
    csr_write(CSR_EXITRAW, sc->exitraw);
    csr_write(CSR_HASHSIG, sc->hashsig);
    
    return 0;
}

void maybe_set_sig_enable(sigriscv_context_t *sc){
    uint32_t upse = sc->idcsr & (IDCSR_UPSE);
    if(upse){
        uint32_t idcsr_new = sc->idcsr | (IDCSR_USE);
        csr_write(CSR_IDCSR, (unsigned long)idcsr_new);
    }
}

#endif
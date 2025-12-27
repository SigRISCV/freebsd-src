#include <sys/types.h>
#include <sys/proc.h>
#include <sys/sigriscv_id.h>
#include <sys/systm.h>
#include <machine/riscvreg.h>
#include <machine/frame.h>

#ifdef SIGRISCV

#define CSR_GPRID_BASE		0x5d0
#define CSR_PCID			0x5f2
#define CSR_IDCSR			0x5f3
#define CSR_ENCMAP          0x5f4
#define CSR_EXITRAW         0x5f5
#define CSR_HASHSIG         0x5f6

// ID mask (24-bit ID)
#define SIGCSR_ID_MASK	0xFFFFFFUL

void init_gpr_ids(struct proc *p)
{
	for (int i = 0; i < 32; i++) p->p_gpr_id[i] = 0;
	p->p_pc_id = 2;
	p->p_idcsr = 0x40000003;
	p->p_encmap = 0;
	p->p_exitraw = 0;
	p->p_hashsig = 0;
}

void copy_gpr_ids(struct proc *from, struct proc *to)
{
	for (int i = 0; i < 32; i++) to->p_gpr_id[i] = from->p_gpr_id[i];
	to->p_pc_id = from->p_pc_id;
	to->p_idcsr = from->p_idcsr;
	to->p_encmap = from->p_encmap;
	to->p_exitraw = from->p_exitraw;
	to->p_hashsig = from->p_hashsig;
}

void clear_gpr_ids(struct proc *p)
{
	for (int i = 0; i < 32; i++) p->p_gpr_id[i] = 0;
	p->p_pc_id = 2;
	p->p_idcsr = 0x40000003;
	p->p_encmap = 0;
	p->p_exitraw = 0;
	p->p_hashsig = 0;
}

void id_activate_sw(struct thread *td)
{
	struct proc *p = td->td_proc;
	
	#define WRITE_GPRID(n) \
		__asm__ __volatile__("csrw %0, %1" :: "i"(CSR_GPRID_BASE + n), "r"((uint64_t)p->p_gpr_id[n]) : "memory")
	
	WRITE_GPRID(0);  WRITE_GPRID(1);  WRITE_GPRID(2);  WRITE_GPRID(3);
	WRITE_GPRID(4);  WRITE_GPRID(5);  WRITE_GPRID(6);  WRITE_GPRID(7);
	WRITE_GPRID(8);  WRITE_GPRID(9);  WRITE_GPRID(10); WRITE_GPRID(11);
	WRITE_GPRID(12); WRITE_GPRID(13); WRITE_GPRID(14); WRITE_GPRID(15);
	WRITE_GPRID(16); WRITE_GPRID(17); WRITE_GPRID(18); WRITE_GPRID(19);
	WRITE_GPRID(20); WRITE_GPRID(21); WRITE_GPRID(22); WRITE_GPRID(23);
	WRITE_GPRID(24); WRITE_GPRID(25); WRITE_GPRID(26); WRITE_GPRID(27);
	WRITE_GPRID(28); WRITE_GPRID(29); WRITE_GPRID(30); WRITE_GPRID(31);
	
	#undef WRITE_GPRID
	
	__asm__ __volatile__("csrw %0, %1" 
			     :: "i"(CSR_PCID), "r"((uint64_t)p->p_pc_id) 
			     : "memory");
	
	__asm__ __volatile__("csrw %0, %1" 
			     :: "i"(CSR_IDCSR), "r"((uint64_t)p->p_idcsr) 
			     : "memory");

	__asm__ __volatile__("csrw %0, %1" 
			     :: "i"(CSR_ENCMAP), "r"((uint64_t)p->p_encmap) 
			     : "memory");

	__asm__ __volatile__("csrw %0, %1" 
			     :: "i"(CSR_EXITRAW), "r"((uint64_t)p->p_exitraw) 
			     : "memory");

	__asm__ __volatile__("csrw %0, %1" 
			     :: "i"(CSR_HASHSIG), "r"((uint64_t)p->p_hashsig) 
			     : "memory");
	
	
	__asm__ __volatile__("fence.i" ::: "memory");
}

void id_save_sw(struct thread *td)
{
	struct proc *p = td->td_proc;
	uint64_t csr_value;
	
	#define READ_GPRID(n) \
		do { \
			__asm__ __volatile__("csrr %0, %1" : "=r"(csr_value) : "i"(CSR_GPRID_BASE + n) : "memory"); \
			p->p_gpr_id[n] = (uint32_t)csr_value; \
		} while (0)
	
	READ_GPRID(0);  READ_GPRID(1);  READ_GPRID(2);  READ_GPRID(3);
	READ_GPRID(4);  READ_GPRID(5);  READ_GPRID(6);  READ_GPRID(7);
	READ_GPRID(8);  READ_GPRID(9);  READ_GPRID(10); READ_GPRID(11);
	READ_GPRID(12); READ_GPRID(13); READ_GPRID(14); READ_GPRID(15);
	READ_GPRID(16); READ_GPRID(17); READ_GPRID(18); READ_GPRID(19);
	READ_GPRID(20); READ_GPRID(21); READ_GPRID(22); READ_GPRID(23);
	READ_GPRID(24); READ_GPRID(25); READ_GPRID(26); READ_GPRID(27);
	READ_GPRID(28); READ_GPRID(29); READ_GPRID(30); READ_GPRID(31);
	
	#undef READ_GPRID
	
	__asm__ __volatile__("csrr %0, %1" 
			     : "=r"(csr_value) 
			     : "i"(CSR_PCID) 
			     : "memory");
	p->p_pc_id = (uint32_t)csr_value;
	
	__asm__ __volatile__("csrr %0, %1" 
			     : "=r"(csr_value) 
			     : "i"(CSR_IDCSR) 
			     : "memory");
	p->p_idcsr = (uint32_t)csr_value;

	__asm__ __volatile__("csrr %0, %1" 
			     : "=r"(csr_value) 
			     : "i"(CSR_ENCMAP) 
			     : "memory");
	p->p_encmap = (uint64_t)csr_value;

	__asm__ __volatile__("csrr %0, %1" 
			     : "=r"(csr_value) 
			     : "i"(CSR_EXITRAW) 
			     : "memory");
	p->p_exitraw = (uint64_t)csr_value;

	__asm__ __volatile__("csrr %0, %1" 
			     : "=r"(csr_value) 
			     : "i"(CSR_HASHSIG) 
			     : "memory");
	p->p_hashsig = (uint64_t)csr_value;
}

void id_save_sw_current(void)
{
	struct thread *td = curthread;
	if (td != NULL && td->td_proc != NULL) {
		id_save_sw(td);
	}
}

void id_activate_sw_current(void)
{
	struct thread *td = curthread;
	if (td != NULL && td->td_proc != NULL) {
		id_activate_sw(td);
	}
}

#endif /* SIGRISCV */
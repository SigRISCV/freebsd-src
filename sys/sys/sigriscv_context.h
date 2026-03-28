#ifndef _SYS_SIGRISCV_CONTEXT_H_
#define	_SYS_SIGRISCV_CONTEXT_H_
#include <sys/types.h>

struct thread;

typedef struct _sigriscv_context{
	uint32_t gpr_id[32];
	uint32_t pc_id;
	uint32_t idcsr;
	uint64_t encmap;
	uint64_t exitraw;
	uint64_t hashsig;
} sigriscv_context_t;

#ifdef SIGRISCV

void get_sigriscv_context(struct thread *td, sigriscv_context_t *sc);
int set_sigriscv_context(struct thread *td, sigriscv_context_t *sc);
void set_sig_enable(struct thread *td);

#endif

#endif

#ifndef _SYS_SIGRISCV_CONTEXT_H_
#define	_SYS_SIGRISCV_CONTEXT_H_
#include <sys/types.h>

#ifdef SIGRISCV

typedef struct _sigriscv_context{
	uint32_t gpr_id[32];
	uint32_t pc_id;
	uint32_t idcsr;
	unsigned long encmap;
	unsigned long exitraw;
	unsigned long hashsig;
} sigriscv_context_t;

void get_sigriscv_context(sigriscv_context_t *sc);
int set_sigriscv_context(sigriscv_context_t *sc);
void maybe_set_sig_enable(sigriscv_context_t *sc);

#endif

#endif

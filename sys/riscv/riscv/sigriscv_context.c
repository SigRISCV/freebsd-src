#include <sys/types.h>
#include <sys/proc.h>
#include <sys/sigriscv_id.h>
#include <sys/sigriscv_context.h>
#include <sys/systm.h>
#include <machine/riscvreg.h>
#include <machine/frame.h>

#ifdef SIGRISCV

#define IDCSR_COUNTER_MASK  0x00ffffffu  /* ID counter: bits [23:0] */
#define IDCSR_USE           0x40000000u  /* SIG enable bit: bit 30 */
#define IDCSR_UPSE          0x80000000u  /* SIG previous enable bit: bit 31 */


void get_sigriscv_context(struct thread *td, sigriscv_context_t *sc){
    id_save_sw(td);
    struct proc *p = td->td_proc;
    for(int i = 0; i < 32; i++)
        sc->gpr_id[i] = p->p_gpr_id[i];
    sc->pc_id = p->p_pc_id;
    sc->idcsr = p->p_idcsr;
    sc->encmap = p->p_encmap;
    sc->exitraw = p->p_exitraw;
    sc->hashsig = p->p_hashsig;
}

int set_sigriscv_context(struct thread *td, sigriscv_context_t *sc){
    struct proc *p = td->td_proc;
    for(int i = 0; i < 32; i++)
        p->p_gpr_id[i] = sc->gpr_id[i];
    p->p_pc_id = sc->pc_id;
    p->p_idcsr = sc->idcsr;
    p->p_encmap = sc->encmap;
    p->p_exitraw = sc->exitraw;
    p->p_hashsig = sc->hashsig;
    id_activate_sw(td);
    return 0;
}

void set_sig_enable(struct thread *td){
    uint64_t idcsr = td->td_proc->p_idcsr;
    idcsr = idcsr | (IDCSR_USE);
    idcsr = idcsr & (~IDCSR_UPSE);

    #define CSR_IDCSR			0x5f3
    __asm__ __volatile__("csrw %0, %1" 
			     :: "i"(CSR_IDCSR), "r"((uint64_t)idcsr) 
			     : "memory");
}

#endif
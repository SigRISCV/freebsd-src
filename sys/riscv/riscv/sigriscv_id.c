#include <sys/types.h>
#include <sys/proc.h>
#include <sys/sigriscv_id.h>
#include <sys/systm.h>
#include <machine/riscvreg.h>
#include <machine/frame.h>

#ifdef SIGRISCV

void init_gpr_ids(struct proc *p)
{
	for (int i = 0; i < 32; i++) p->p_sigriscv_context.gpr_id[i] = 0;
	p->p_sigriscv_context.pc_id = 2;
	p->p_sigriscv_context.idcsr = 0x40000003;
	p->p_sigriscv_context.encmap = 0;
	p->p_sigriscv_context.exitraw = 0;
	p->p_sigriscv_context.hashsig = 0;
}

void copy_gpr_ids(struct proc *from, struct proc *to)
{
	for (int i = 0; i < 32; i++) to->p_sigriscv_context.gpr_id[i] = from->p_sigriscv_context.gpr_id[i];
	to->p_sigriscv_context.pc_id = from->p_sigriscv_context.pc_id;
	to->p_sigriscv_context.idcsr = from->p_sigriscv_context.idcsr;
	to->p_sigriscv_context.encmap = from->p_sigriscv_context.encmap;
	to->p_sigriscv_context.exitraw = from->p_sigriscv_context.exitraw;
	to->p_sigriscv_context.hashsig = from->p_sigriscv_context.hashsig;
}

void clear_gpr_ids(struct proc *p)
{
	for (int i = 0; i < 32; i++) p->p_sigriscv_context.gpr_id[i] = 0;
	p->p_sigriscv_context.pc_id = 2;
	p->p_sigriscv_context.idcsr = 0x40000003;
	p->p_sigriscv_context.encmap = 0;
	p->p_sigriscv_context.exitraw = 0;
	p->p_sigriscv_context.hashsig = 0;
}

void id_activate_sw(struct thread *td)
{
	struct proc *p = td->td_proc;
	set_sigriscv_context(&p->p_sigriscv_context);
}

void id_save_sw(struct thread *td)
{
	struct proc *p = td->td_proc;
	get_sigriscv_context(&p->p_sigriscv_context);
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
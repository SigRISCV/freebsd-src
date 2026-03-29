#ifndef _SYS_SIGRISCV_ID_H_
#define	_SYS_SIGRISCV_ID_H_

#include <sys/types.h>
#include <sys/sigriscv_context.h>

struct thread;
struct proc;

#ifdef SIGRISCV

void init_gpr_ids(struct proc *p);

void copy_gpr_ids(struct proc *from, struct proc *to);

void clear_gpr_ids(struct proc *p);

void id_activate_sw(struct thread *td);

void id_save_sw(struct thread *td);

void id_save_sw_current(void);

void id_activate_sw_current(void);

#endif /* SIGRISCV */
#endif /* !_SYS_SIGRISCV_ID_H_ */


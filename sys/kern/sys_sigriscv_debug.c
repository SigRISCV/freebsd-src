#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/proc.h>
#include <sys/syscallsubr.h>
#include <sys/errno.h>
#include <sys/sigriscv_key.h>
#ifdef SIGRISCV
#include <machine/riscvreg.h>
#include <sys/sigriscv_context.h>
#endif

#include <sys/sysproto.h>
#ifdef SIGRISCV

/*
   System call to get SigRISCV debug information for the current process.
   Includes:
   - Process ID
   - SKEY CSR values
   - Encrypted SKEY buffer values
   - GPRID CSR values
 */
int
sys_sigriscv_debug_info(struct thread *td, struct sigriscv_debug_info_args *uap)
{
	struct sigriscv_debug_info info;
	struct proc *p = td->td_proc;
	int error;

	if (uap->info == NULL) return (EFAULT);

	bzero(&info, sizeof(info));
	info.pid = p->p_pid;
	info.ppid = kern_getppid(td);
	info.buffer_addr = (uint64_t)(uintptr_t)p->p_skey_secret_buffer;

	bcopy(p->p_skey_secret_buffer, info.encrypted_buffer, 
	      sizeof(p->p_skey_secret_buffer));

	info.skeyl = csr_read(0x5f0);
	info.skeyh = csr_read(0x5f1);

	// Provide both PCB (saved user-space state) and CSR (current kernel state) values.
	
	for (int i = 0; i < 32; i++) {
		info.gpr_id[i] = p->p_sigriscv_context.gpr_id[i];
	}
	info.pc_id = p->p_sigriscv_context.pc_id;
	info.idcsr = p->p_sigriscv_context.idcsr;
	
	// Read from CSRs
	info.gpr_id_csr[0] = csr_read(0x5d0);
	info.gpr_id_csr[1] = csr_read(0x5d1);
	info.gpr_id_csr[2] = csr_read(0x5d2);
	info.gpr_id_csr[3] = csr_read(0x5d3);
	info.gpr_id_csr[4] = csr_read(0x5d4);
	info.gpr_id_csr[5] = csr_read(0x5d5);
	info.gpr_id_csr[6] = csr_read(0x5d6);
	info.gpr_id_csr[7] = csr_read(0x5d7);
	info.gpr_id_csr[8] = csr_read(0x5d8);
	info.gpr_id_csr[9] = csr_read(0x5d9);
	info.gpr_id_csr[10] = csr_read(0x5da);
	info.gpr_id_csr[11] = csr_read(0x5db);
	info.gpr_id_csr[12] = csr_read(0x5dc);
	info.gpr_id_csr[13] = csr_read(0x5dd);
	info.gpr_id_csr[14] = csr_read(0x5de);
	info.gpr_id_csr[15] = csr_read(0x5df);
	info.gpr_id_csr[16] = csr_read(0x5e0);
	info.gpr_id_csr[17] = csr_read(0x5e1);
	info.gpr_id_csr[18] = csr_read(0x5e2);
	info.gpr_id_csr[19] = csr_read(0x5e3);
	info.gpr_id_csr[20] = csr_read(0x5e4);
	info.gpr_id_csr[21] = csr_read(0x5e5);
	info.gpr_id_csr[22] = csr_read(0x5e6);
	info.gpr_id_csr[23] = csr_read(0x5e7);
	info.gpr_id_csr[24] = csr_read(0x5e8);
	info.gpr_id_csr[25] = csr_read(0x5e9);
	info.gpr_id_csr[26] = csr_read(0x5ea);
	info.gpr_id_csr[27] = csr_read(0x5eb);
	info.gpr_id_csr[28] = csr_read(0x5ec);
	info.gpr_id_csr[29] = csr_read(0x5ed);
	info.gpr_id_csr[30] = csr_read(0x5ee);
	info.gpr_id_csr[31] = csr_read(0x5ef);
	
	info.pc_id_csr = csr_read(0x5f2);
	info.idcsr_csr = csr_read(0x5f3);

	error = copyout(&info, (struct sigriscv_debug_info *)uap->info, sizeof(info));
	if (error != 0) return (error);
	return (0);
}

#else /* !SIGRISCV */

int
sys_sigriscv_debug_info(struct thread *td, struct sigriscv_debug_info_args *uap)
{
	return (ENOSYS);
}

#endif /* SIGRISCV */


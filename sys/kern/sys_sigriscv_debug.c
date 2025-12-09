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

	info.gpr_id[0] = csr_read(0x5d0);
	info.gpr_id[1] = csr_read(0x5d1);
	info.gpr_id[2] = csr_read(0x5d2);
	info.gpr_id[3] = csr_read(0x5d3);
	info.gpr_id[4] = csr_read(0x5d4);
	info.gpr_id[5] = csr_read(0x5d5);
	info.gpr_id[6] = csr_read(0x5d6);
	info.gpr_id[7] = csr_read(0x5d7);
	info.gpr_id[8] = csr_read(0x5d8);
	info.gpr_id[9] = csr_read(0x5d9);
	info.gpr_id[10] = csr_read(0x5da);
	info.gpr_id[11] = csr_read(0x5db);
	info.gpr_id[12] = csr_read(0x5dc);
	info.gpr_id[13] = csr_read(0x5dd);
	info.gpr_id[14] = csr_read(0x5de);
	info.gpr_id[15] = csr_read(0x5df);
	info.gpr_id[16] = csr_read(0x5e0);
	info.gpr_id[17] = csr_read(0x5e1);
	info.gpr_id[18] = csr_read(0x5e2);
	info.gpr_id[19] = csr_read(0x5e3);
	info.gpr_id[20] = csr_read(0x5e4);
	info.gpr_id[21] = csr_read(0x5e5);
	info.gpr_id[22] = csr_read(0x5e6);
	info.gpr_id[23] = csr_read(0x5e7);
	info.gpr_id[24] = csr_read(0x5e8);
	info.gpr_id[25] = csr_read(0x5e9);
	info.gpr_id[26] = csr_read(0x5ea);
	info.gpr_id[27] = csr_read(0x5eb);
	info.gpr_id[28] = csr_read(0x5ec);
	info.gpr_id[29] = csr_read(0x5ed);
	info.gpr_id[30] = csr_read(0x5ee);
	info.gpr_id[31] = csr_read(0x5ef);

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


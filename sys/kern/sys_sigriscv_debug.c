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

	__asm__ __volatile__("csrr %0, %1" : "=r"(info.skeyl) : "i"(CSR_SKEYL) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.skeyh) : "i"(CSR_SKEYH) : "memory");

	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[0]) : "i"(0x5d0) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[1]) : "i"(0x5d1) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[2]) : "i"(0x5d2) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[3]) : "i"(0x5d3) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[4]) : "i"(0x5d4) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[5]) : "i"(0x5d5) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[6]) : "i"(0x5d6) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[7]) : "i"(0x5d7) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[8]) : "i"(0x5d8) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[9]) : "i"(0x5d9) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[10]) : "i"(0x5da) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[11]) : "i"(0x5db) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[12]) : "i"(0x5dc) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[13]) : "i"(0x5dd) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[14]) : "i"(0x5de) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[15]) : "i"(0x5df) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[16]) : "i"(0x5e0) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[17]) : "i"(0x5e1) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[18]) : "i"(0x5e2) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[19]) : "i"(0x5e3) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[20]) : "i"(0x5e4) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[21]) : "i"(0x5e5) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[22]) : "i"(0x5e6) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[23]) : "i"(0x5e7) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[24]) : "i"(0x5e8) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[25]) : "i"(0x5e9) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[26]) : "i"(0x5ea) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[27]) : "i"(0x5eb) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[28]) : "i"(0x5ec) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[29]) : "i"(0x5ed) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[30]) : "i"(0x5ee) : "memory");
	__asm__ __volatile__("csrr %0, %1" : "=r"(info.gpr_id[31]) : "i"(0x5ef) : "memory");

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


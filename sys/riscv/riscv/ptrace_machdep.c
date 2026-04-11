/*-
 * Copyright (c) 2014 Andrew Turner
 * Copyright (c) 2015-2017 Ruslan Bukin <br@bsdpad.com>
 * All rights reserved.
 *
 * Portions of this software were developed by SRI International and the
 * University of Cambridge Computer Laboratory under DARPA/AFRL contract
 * FA8750-10-C-0237 ("CTSRD"), as part of the DARPA CRASH research programme.
 *
 * Portions of this software were developed by the University of Cambridge
 * Computer Laboratory as part of the CTSRD Project, with support from the
 * UK Higher Education Innovation Fund (HEIF).
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/elf.h>
#include <sys/exec.h>
#include <sys/imgact.h>
#include <sys/kdb.h>
#include <sys/kernel.h>
#include <sys/ktr.h>
#include <sys/limits.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/proc.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/rwlock.h>
#include <sys/sched.h>
#include <sys/signalvar.h>
#include <sys/syscallsubr.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>
#include <sys/ucontext.h>
#include <sys/sigriscv_context.h>

#include <machine/cpu.h>
#include <machine/pcb.h>
#include <machine/pte.h>
#include <machine/riscvreg.h>
#include <machine/sbi.h>
#include <machine/trap.h>

#ifdef SIGRISCV
static bool
get_riscv_sigriscv(struct regset *rs, struct thread *td, void *buf,
    size_t *sizep)
{
	sigriscv_context_t sc;

	if (buf != NULL) {
		KASSERT(*sizep == sizeof(sc), ("%s: invalid size", __func__));
		sc = td->td_proc->p_sigriscv_context;
		if (td == curthread) {
			get_sigriscv_context(&sc);
			td->td_proc->p_sigriscv_context = sc;
		}
		memcpy(buf, &sc, sizeof(sc));
	}
	*sizep = sizeof(sc);
	return (true);
}

static bool
set_riscv_sigriscv(struct regset *rs, struct thread *td, void *buf,
    size_t size)
{
	sigriscv_context_t *sc;

	KASSERT(size == sizeof(*sc), ("%s: invalid size", __func__));
	sc = buf;
	td->td_proc->p_sigriscv_context = *sc;
	if (td == curthread)
		return (set_sigriscv_context(&td->td_proc->p_sigriscv_context) == 0);
	return (true);
}

static struct regset regset_riscv_sigriscv = {
	.note = NT_RISCV_SIGRISCV,
	.size = sizeof(sigriscv_context_t),
	.get = get_riscv_sigriscv,
	.set = set_riscv_sigriscv,
};
ELF_REGSET(regset_riscv_sigriscv);
#endif

int
ptrace_set_pc(struct thread *td, u_long addr)
{

	td->td_frame->tf_sepc = addr;
	return (0);
}

int
ptrace_single_step(struct thread *td)
{

	/* TODO; */
	return (EOPNOTSUPP);
}

int
ptrace_clear_single_step(struct thread *td)
{

	/* TODO; */
	return (EOPNOTSUPP);
}

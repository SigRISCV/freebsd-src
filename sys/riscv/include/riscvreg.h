/*-
 * Copyright (c) 2015-2024 Ruslan Bukin <br@bsdpad.com>
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

#ifndef _MACHINE_RISCVREG_H_
#define	_MACHINE_RISCVREG_H_

#define	SCAUSE_INTR			(1ul << 63)
#define	SCAUSE_CODE			(~SCAUSE_INTR)
#define	SCAUSE_INST_MISALIGNED		0
#define	SCAUSE_INST_ACCESS_FAULT	1
#define	SCAUSE_ILLEGAL_INSTRUCTION	2
#define	SCAUSE_BREAKPOINT		3
#define	SCAUSE_LOAD_MISALIGNED		4
#define	SCAUSE_LOAD_ACCESS_FAULT	5
#define	SCAUSE_STORE_MISALIGNED		6
#define	SCAUSE_STORE_ACCESS_FAULT	7
#define	SCAUSE_ECALL_USER		8
#define	SCAUSE_ECALL_SUPERVISOR		9
#define	SCAUSE_VIRTUAL_SUPERVISOR_ECALL	10
#define	SCAUSE_MACHINE_ECALL		11
#define	SCAUSE_INST_PAGE_FAULT		12
#define	SCAUSE_LOAD_PAGE_FAULT		13
#define	SCAUSE_STORE_PAGE_FAULT		15
#define	SCAUSE_FETCH_GUEST_PAGE_FAULT	20
#define	SCAUSE_LOAD_GUEST_PAGE_FAULT	21
#define	SCAUSE_VIRTUAL_INSTRUCTION	22
#define	SCAUSE_STORE_GUEST_PAGE_FAULT	23

#define	SSTATUS_UIE			(1 << 0)
#define	SSTATUS_SIE			(1 << 1)
#define	SSTATUS_UPIE			(1 << 4)
#define	SSTATUS_SPIE			(1 << 5)
#define	SSTATUS_SPIE_SHIFT		5
#define	SSTATUS_SPP			(1 << 8)
#define	SSTATUS_SPP_SHIFT		8
#define	SSTATUS_FS_SHIFT		13
#define	SSTATUS_FS_OFF			(0x0 << SSTATUS_FS_SHIFT)
#define	SSTATUS_FS_INITIAL		(0x1 << SSTATUS_FS_SHIFT)
#define	SSTATUS_FS_CLEAN		(0x2 << SSTATUS_FS_SHIFT)
#define	SSTATUS_FS_DIRTY		(0x3 << SSTATUS_FS_SHIFT)
#define	SSTATUS_FS_MASK			(0x3 << SSTATUS_FS_SHIFT)
#define	SSTATUS_XS_SHIFT		15
#define	SSTATUS_XS_MASK			(0x3 << SSTATUS_XS_SHIFT)
#define	SSTATUS_SUM			(1 << 18)
#if __riscv_xlen == 64
#define	SSTATUS_SD			(1ul << 63)
#else
#define	SSTATUS_SD			(1 << 31)
#endif

#define	MSTATUS_UIE			(1 << 0)
#define	MSTATUS_SIE			(1 << 1)
#define	MSTATUS_HIE			(1 << 2)
#define	MSTATUS_MIE			(1 << 3)
#define	MSTATUS_UPIE			(1 << 4)
#define	MSTATUS_SPIE			(1 << 5)
#define	MSTATUS_SPIE_SHIFT		5
#define	MSTATUS_HPIE			(1 << 6)
#define	MSTATUS_MPIE			(1 << 7)
#define	MSTATUS_MPIE_SHIFT		7
#define	MSTATUS_SPP			(1 << 8)
#define	MSTATUS_SPP_SHIFT		8
#define	MSTATUS_HPP_MASK		0x3
#define	MSTATUS_HPP_SHIFT		9
#define	MSTATUS_MPP_MASK		0x3
#define	MSTATUS_MPP_SHIFT		11
#define	MSTATUS_FS_MASK			0x3
#define	MSTATUS_FS_SHIFT		13
#define	MSTATUS_XS_MASK			0x3
#define	MSTATUS_XS_SHIFT		15
#define	MSTATUS_MPRV			(1 << 17)
#define	MSTATUS_PUM			(1 << 18)
#define	MSTATUS_VM_MASK			0x1f
#define	MSTATUS_VM_SHIFT		24
#define	 MSTATUS_VM_MBARE		0
#define	 MSTATUS_VM_MBB			1
#define	 MSTATUS_VM_MBBID		2
#define	 MSTATUS_VM_SV32		8
#define	 MSTATUS_VM_SV39		9
#define	 MSTATUS_VM_SV48		10
#define	 MSTATUS_VM_SV57		11
#define	 MSTATUS_VM_SV64		12
#if __riscv_xlen == 64
#define	MSTATUS_SD			(1ul << 63)
#else
#define	MSTATUS_SD			(1 << 31)
#endif

#define	MSTATUS_PRV_U			0	/* user */
#define	MSTATUS_PRV_S			1	/* supervisor */
#define	MSTATUS_PRV_H			2	/* hypervisor */
#define	MSTATUS_PRV_M			3	/* machine */

#define	HSTATUS_VSBE	(1 << 5)
#define	HSTATUS_GVA	(1 << 6)
#define	HSTATUS_SPV	(1 << 7)
#define	HSTATUS_SPVP	(1 << 8)
#define	HSTATUS_HU	(1 << 9)
#define	HSTATUS_VGEIN_S	12
#define	HSTATUS_VGEIN_M	(0xf << HSTATUS_VGEIN_S)
#define	HSTATUS_VTVM	(1 << 20)
#define	HSTATUS_VTW	(1 << 21)
#define	HSTATUS_VTSR	(1 << 22)

#define	MIE_USIE	(1 << 0)
#define	MIE_SSIE	(1 << 1)
#define	MIE_HSIE	(1 << 2)
#define	MIE_MSIE	(1 << 3)
#define	MIE_UTIE	(1 << 4)
#define	MIE_STIE	(1 << 5)
#define	MIE_HTIE	(1 << 6)
#define	MIE_MTIE	(1 << 7)

#define	MIP_USIP	(1 << 0)
#define	MIP_SSIP	(1 << 1)
#define	MIP_HSIP	(1 << 2)
#define	MIP_MSIP	(1 << 3)
#define	MIP_UTIP	(1 << 4)
#define	MIP_STIP	(1 << 5)
#define	MIP_HTIP	(1 << 6)
#define	MIP_MTIP	(1 << 7)

#define	SIE_USIE	(1 << 0)
#define	SIE_SSIE	(1 << 1)
#define	SIE_UTIE	(1 << 4)
#define	SIE_STIE	(1 << 5)
#define	SIE_UEIE	(1 << 8)
#define	SIE_SEIE	(1 << 9)

#define	MIP_SEIP	(1 << 9)

#define	HVIP_VSSIP	(1 << 2)
#define	HVIP_VSTIP	(1 << 6)
#define	HVIP_VSEIP	(1 << 10)

#define	HIE_VSSIE	(1 << 2)
#define	HIE_VSTIE	(1 << 6)
#define	HIE_VSEIE	(1 << 10)
#define	HIE_SGEIE	(1 << 12)

/* Note: sip register has no SIP_STIP bit in Spike simulator */
#define	SIP_SSIP	(1 << 1)
#define	SIP_STIP	(1 << 5)

#define	HENVCFG_STCE	(1UL << 63)
#define	HENVCFG_PBMTE	(1UL << 62)
#define	HENVCFG_CBZE	(1UL << 7)
#define	HENVCFG_CBCFE	(1UL << 6)
#define	HENVCFG_CBIE_S	4
#define	HENVCFG_CBIE_M	(0x3 << HENVCFG_CBIE_S)
#define	HENVCFG_FIOM	(1UL << 0)

#define	HCOUNTEREN_CY	(1UL << 0) /* Cycle */
#define	HCOUNTEREN_TM	(1UL << 1) /* Time */
#define	HCOUNTEREN_IR	(1UL << 2) /* Instret */

#define	SATP_PPN_S	0
#define	SATP_PPN_M	(0xfffffffffffUL << SATP_PPN_S)
#define	SATP_ASID_S	44
#define	SATP_ASID_M	(0xffffUL << SATP_ASID_S)
#define	SATP_MODE_S	60
#define	SATP_MODE_M	(0xfUL << SATP_MODE_S)
#define	SATP_MODE_SV39	(8ULL << SATP_MODE_S)
#define	SATP_MODE_SV48	(9ULL << SATP_MODE_S)

#define	XLEN		__riscv_xlen
#define	XLEN_BYTES	(XLEN / 8)
#define	INSN_SIZE	4
#define	INSN_C_SIZE	2

#define	X_RA	1
#define	X_SP	2
#define	X_GP	3
#define	X_TP	4
#define	X_T0	5
#define	X_T1	6
#define	X_T2	7
#define	X_T3	28

#define	RD_SHIFT	7
#define	RD_MASK		(0x1f << RD_SHIFT)
#define	RS1_SHIFT	15
#define	RS1_MASK	(0x1f << RS1_SHIFT)
#define	RS1_SP		(X_SP << RS1_SHIFT)
#define	RS2_SHIFT	20
#define	RS2_MASK	(0x1f << RS2_SHIFT)
#define	RS2_RA		(X_RA << RS2_SHIFT)
#define	IMM_SHIFT	20
#define	IMM_MASK	(0xfff << IMM_SHIFT)

#define	RS2_C_SHIFT	2
#define	RS2_C_MASK	(0x1f << RS2_C_SHIFT)
#define	RS2_C_RA	(X_RA << RS2_C_SHIFT)

#define	CSR_ZIMM(val)							\
	(__builtin_constant_p(val) && ((u_long)(val) < 32))

#define	csr_swap(csr, val)						\
({	u_long ret;							\
	if (CSR_ZIMM(val))  						\
		__asm __volatile("csrrwi %0, " #csr ", %1"		\
				: "=r" (ret) : "i" (val));		\
	else 								\
		__asm __volatile("csrrw %0, " #csr ", %1"		\
				: "=r" (ret) : "r" (val));		\
	ret;								\
})

#define	csr_write(csr, val)						\
({	if (CSR_ZIMM(val)) 						\
		__asm __volatile("csrwi " #csr ", %0" :: "i" (val));	\
	else 								\
		__asm __volatile("csrw " #csr ", %0" ::  "r" (val));	\
})

#define	csr_set(csr, val)						\
({	if (CSR_ZIMM(val)) 						\
		__asm __volatile("csrsi " #csr ", %0" :: "i" (val));	\
	else								\
		__asm __volatile("csrs " #csr ", %0" :: "r" (val));	\
})

#define	csr_clear(csr, val)						\
({	if (CSR_ZIMM(val))						\
		__asm __volatile("csrci " #csr ", %0" :: "i" (val));	\
	else								\
		__asm __volatile("csrc " #csr ", %0" :: "r" (val));	\
})

#define	csr_read(csr)							\
({	u_long val;							\
	__asm __volatile("csrr %0, " #csr : "=r" (val));		\
	val;								\
})

#if __riscv_xlen == 32
#define	csr_read64(csr)							\
({	uint64_t val;							\
	uint32_t high, low;						\
	__asm __volatile("1: "						\
			 "csrr t0, " #csr "h\n"				\
			 "csrr %0, " #csr "\n"				\
			 "csrr %1, " #csr "h\n"				\
			 "bne t0, %1, 1b"				\
			 : "=r" (low), "=r" (high)			\
			 :						\
			 : "t0");					\
	val = (low | ((uint64_t)high << 32));				\
	val;								\
})
#else
#define	csr_read64(csr)		((uint64_t)csr_read(csr))
#endif

#ifdef SIGRISCV
/* SigRISCV ls/ss instruction macros */
/* ls rd, imm(rs1) - Load with decryption */
#define ls(rd, imm, rs1) \
	__asm__ __volatile__("ls %0, %1(%2)" \
			     : "=r"(rd) \
			     : "i"(imm), "r"(rs1) \
			     : "memory")

/* ss rs2, imm(rs1) - Store with encryption */
#define ss(rs2, imm, rs1) \
	__asm__ __volatile__("ss %0, %1(%2)" \
			     : \
			     : "r"(rs2), "i"(imm), "r"(rs1) \
			     : "memory")

/* ==================== xsig meta inst ==================== */

// setrawid: void* (void*)
#define xsig_setrawid(val) \
    __builtin_riscv_xsig_setrawid((void*)(val))

// setnewid: void* (void*)
#define xsig_setnewid(val) \
    __builtin_riscv_xsig_setnewid((void*)(val))

// moveid: void* (void*, void*)
#define xsig_moveid(dest, src) \
	((src) - (uint64_t)(src) + (uint64_t)(dest))
/* ==================== xsig load/store ==================== */

// load_sig: void* (void*)
#define xsig_load_sig(addr) \
    __builtin_riscv_xsig_load_sig((void*)(addr))

// store_sig: void (void*, void*)
#define xsig_store_sig(addr, val) \
    __builtin_riscv_xsig_store_sig((void*)(addr), (void*)(val))

// load_dyn: void* (void*)
#define xsig_load_dyn(addr) \
    __builtin_riscv_xsig_load_dyn((void*)(addr))

// store_dyn: void (void*, void*)
#define xsig_store_dyn(addr, val) \
    __builtin_riscv_xsig_store_dyn((void*)(addr), (void*)(val))

/* ==================== xsig debug inst ==================== */

// debug_sig: void ()
#define xsig_debug_sig() \
    __builtin_riscv_xsig_debug_sig()

// debug_chr: void (uint64_t)
#define xsig_debug_chr(val) \
    __builtin_riscv_xsig_debug_chr((uint64_t)(val))

// debug_int: void (uint64_t)
#define xsig_debug_int(val) \
    __builtin_riscv_xsig_debug_int((uint64_t)(val))

// debug_hex: void (uint64_t)
#define xsig_debug_hex(val) \
    __builtin_riscv_xsig_debug_ptr((uint64_t)xsig_setrawid((val)))

// debug_ptr: void (void*)
#define xsig_debug_ptr(ptr) \
    __builtin_riscv_xsig_debug_ptr((void*)(ptr))

// debug_csr: void (uint64_t)
#define xsig_debug_csr(val) \
    __builtin_riscv_xsig_debug_csr((uint64_t)(val))

// debug_str: void (const char*)
#define xsig_debug_str(str) \
	{										\
		const char* p = (const char*)(str);	\
		while (*p) {						\
			xsig_debug_chr(*p++);			\
		}									\
	}

/* CSR definitions for SigRISCV */
#define CSR_MKEYL		0x7f0
#define CSR_MKEYH		0x7f1
#define CSR_SKEYL		0x5f0
#define CSR_SKEYH		0x5f1
#define CSR_GPRID0		0x5d0
#define CSR_GPRID1		0x5d1
#define CSR_GPRID2		0x5d2
#define CSR_GPRID3		0x5d3
#define CSR_GPRID4		0x5d4
#define CSR_GPRID5		0x5d5
#define CSR_GPRID6		0x5d6
#define CSR_GPRID7		0x5d7
#define CSR_GPRID8		0x5d8
#define CSR_GPRID9		0x5d9
#define CSR_GPRID10		0x5da
#define CSR_GPRID11		0x5db
#define CSR_GPRID12		0x5dc
#define CSR_GPRID13		0x5dd
#define CSR_GPRID14		0x5de
#define CSR_GPRID15		0x5df
#define CSR_GPRID16		0x5e0
#define CSR_GPRID17		0x5e1
#define CSR_GPRID18		0x5e2
#define CSR_GPRID19		0x5e3
#define CSR_GPRID20		0x5e4
#define CSR_GPRID21		0x5e5
#define CSR_GPRID22		0x5e6
#define CSR_GPRID23		0x5e7
#define CSR_GPRID24		0x5e8
#define CSR_GPRID25		0x5e9
#define CSR_GPRID26		0x5ea
#define CSR_GPRID27		0x5eb
#define CSR_GPRID28		0x5ec
#define CSR_GPRID29		0x5ed
#define CSR_GPRID30		0x5ee
#define CSR_GPRID31		0x5ef
#define CSR_PCID		0x5f2
#define CSR_IDCSR		0x5f3
#define CSR_ENCMAP		0x5f4
#define CSR_EXITRAW		0x5f5
#define CSR_HASHSIG	    0x5f6
#endif /* SIGRISCV */

#endif /* !_MACHINE_RISCVREG_H_ */

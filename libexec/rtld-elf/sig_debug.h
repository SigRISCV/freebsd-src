#ifndef __SIG_DEBUG_H__
#define __SIG_DEBUG_H__

#include <machine/riscvreg.h>

/*
 * Debug control macro
 * Set SIGRISCV_DEBUG to enable debug output
 */
#ifdef SIGRISCV_DEBUG
    #define SIG_DEBUG(code) { code; }
#else
    #define SIG_DEBUG(code) {}
#endif

/*
 * Debug instruction format: debug rd, rs1, imm
 *   imm=0: output all CSRs
 *   imm=1: output rs1 as char
 *   imm=2: output rs1 as int
 *   imm=3: output rs1 as pointer (with ID), assign ID to rd
 *   imm=4: output CSR at address rs1, assign value to rd
 */

#define debug_str(str) xsig_debug_str(str)
#define debug_int(val) xsig_debug_int(val)
#define debug_ptr(ptr) xsig_debug_ptr(ptr)
#define debug_hex(val) xsig_debug_hex(val)
#define debug_chr(val) xsig_debug_chr(val)
#define debug_csr(addr) xsig_debug_csr(addr)
#define debug_newline() xsig_debug_str("\n")

#endif /* __SIG_DEBUG_H__ */

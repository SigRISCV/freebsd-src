#ifndef _SYS_SIGRISCV_KEY_H_
#define	_SYS_SIGRISCV_KEY_H_

#include <sys/types.h>

struct thread;

struct sigriscv_debug_info {
	pid_t pid;
	pid_t ppid;
	uint64_t buffer_addr;
	uint64_t skeyl;
	uint64_t skeyh;
	uint64_t encrypted_buffer[2];
	uint64_t gpr_id[32];  /* GPR shadow IDs (x0-x31), CSR 0x5d0-0x5ef */
};

#ifdef SIGRISCV


void construct_update_skey(uint64_t key_buffer[2]);

void load_update_skey(uint64_t key_buffer[2]);

void reencrypt_skey(uint64_t buffer_from[2], uint64_t buffer_to[2]);

void key_activate_sw(struct thread *td);

#endif /* SIGRISCV */
#endif /* !_SYS_SIGRISCV_KEY_H_ */


#include <sys/types.h>
#include <sys/proc.h>
#include <sys/sigriscv_key.h>
#include <sys/systm.h>
#include <machine/riscvreg.h>

#ifdef SIGRISCV

struct key_pair {
	uint64_t keyl;
	uint64_t keyh;
};

static inline struct key_pair construct_new_skey(void) {
	volatile int dummy_data = 0;
	int cnt;
	unsigned long entropy_low, entropy_high;
	unsigned long encrypted_low, encrypted_high;
	unsigned long __attribute__((aligned(8))) key_buffer[1];

	#define cycle_read_entropy() ({cnt = 10; while(cnt--){ dummy_data++; }; csr_read(0xc00);})

	entropy_low = cycle_read_entropy();
	__asm__ __volatile__("sd %0, 0(%1)" : : "r"(entropy_low), "r"(key_buffer) : "memory");
	ls(encrypted_low, 0, key_buffer);

	entropy_high = cycle_read_entropy();
	__asm__ __volatile__("sd %0, 0(%1)" : : "r"(entropy_high), "r"(key_buffer) : "memory");
	ls(encrypted_high, 0, key_buffer);

	key_buffer[0] = 0;
	#undef cycle_read_entropy

	struct key_pair keys;
	keys.keyl = encrypted_low;
	keys.keyh = encrypted_high;
	return keys;
}

static inline void encrypt_and_store_key(struct key_pair key, uint64_t buffer[2], uint64_t buffer_addr) {
	unsigned long *addr = (unsigned long *)buffer_addr;
	ss(key.keyl, 0, addr);
	ss(key.keyh, 8, addr);
}

static inline struct key_pair load_and_decrypt_key(uint64_t buffer[2], uint64_t buffer_addr) {
	unsigned long *addr = (unsigned long *)buffer_addr;
	struct key_pair key;
	unsigned long decrypted;

	ls(decrypted, 0, addr);
	key.keyl = decrypted;

	ls(decrypted, 8, addr);
	key.keyh = decrypted;

	return key;
}

void construct_update_skey(uint64_t key_buffer[2]) {
	struct key_pair key;
	uint64_t buffer_addr = (uint64_t)key_buffer;
	key = construct_new_skey();

	// Encrypt and store to PCB
	encrypt_and_store_key(key, key_buffer, buffer_addr);

	// Update skey CSR
	__asm__ __volatile__("csrw %0, %1" :: "i"(CSR_SKEYL), "r"(key.keyl) : "memory");
	__asm__ __volatile__("csrw %0, %1" :: "i"(CSR_SKEYH), "r"(key.keyh) : "memory");
	__asm__ __volatile__("fence.i" ::: "memory");
}

void load_update_skey(uint64_t key_buffer[2]) {
	struct key_pair key;
	uint64_t buffer_addr = (uint64_t)key_buffer;

	// Load and decrypt key from buffer
	key = load_and_decrypt_key(key_buffer, buffer_addr);

	// Update skey CSR
	__asm__ __volatile__("csrw %0, %1" :: "i"(CSR_SKEYL), "r"(key.keyl) : "memory");
	__asm__ __volatile__("csrw %0, %1" :: "i"(CSR_SKEYH), "r"(key.keyh) : "memory");
	__asm__ __volatile__("fence.i" ::: "memory");
}

void reencrypt_skey(uint64_t buffer_from[2], uint64_t buffer_to[2]) {
	struct key_pair key;
	uint64_t from_addr = (uint64_t)buffer_from;
	uint64_t to_addr = (uint64_t)buffer_to;

	// Load and decrypt key from source buffer
	key = load_and_decrypt_key(buffer_from, from_addr);

	// Encrypt and store to destination buffer using new address as tweak
	encrypt_and_store_key(key, buffer_to, to_addr);
}

void key_activate_sw(struct thread *td) {
	uint64_t *buffer = td->td_proc->p_skey_secret_buffer;
	load_update_skey(buffer);
}

#endif /* SIGRISCV */


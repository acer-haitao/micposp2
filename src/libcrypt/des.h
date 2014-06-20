#ifndef __DES__H_
#define __DES__H_

#include "types.h"

#define CRYPTO_TFM_REQ_WEAK_KEY		0x00000100
#define CRYPTO_TFM_RES_WEAK_KEY		0x00100000
#define CRYPTO_TFM_RES_BAD_KEY_SCHED 	0x00400000

#define DES_KEY_SIZE 8
#define DES_EXPKEY_WORDS 32
#define DES_BLOCK_SIZE 8

#define DES3_EDE_KEY_SIZE	(3 * DES_KEY_SIZE)
#define DES3_EDE_EXPKEY_WORDS	(3 * DES_EXPKEY_WORDS)
#define DES3_EDE_BLOCK_SIZE	DES_BLOCK_SIZE

struct des_ctx {
	u8 iv[DES_BLOCK_SIZE];
	u32 expkey[DES_EXPKEY_WORDS];
};

struct des3_ede_ctx {
	u8 iv[DES_BLOCK_SIZE];
	u32 expkey[DES3_EDE_EXPKEY_WORDS];
};

int des_setkey(void *ctx, const u8 *key, unsigned int keylen, u32 *flags);
void des_encrypt(void *ctx, u8 *dst, const u8 *src);
void des_decrypt(void *ctx, u8 *dst, const u8 *src);

int des3_ede_setkey(void *ctx, const u8 *key, unsigned int keylen, u32 *flags);
void des3_ede_encrypt(void *ctx, u8 *dst, const u8 *src);
void des3_ede_decrypt(void *ctx, u8 *dst, const u8 *src);

#endif

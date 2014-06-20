/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file  crypto.c
 * @brief 常用加密算法接口。
 */
#include <string.h>
#include <stdlib.h>
#include "des.h"
#include "byteo.h"
#include "crypto.h"

/**
 * @brief 用DES算法加密数据。
 * 
 * @param key 加密密钥（8字节）。
 * @param data 输入加密数据，输出加密结果。加密数据的长度必须是8的倍数。
 * @param nbytes 加密数据的长度。
 * 
 * @return 加密结果的长度，计算错误返回负数。
 */
S16 des(const U8 key[8], U8 *data, const U16 nbytes)
{
	U16 i;
	U32 flags = 0;
	struct des_ctx ctx;
	U8 *mdata;
	
	if (!data) {
		errno = EBADF;
		return -1;
	}
	if (nbytes & 0x07) {
		errno = EINVAL;
		return -1;
	}
	if (des_setkey(&ctx, key, 8, &flags) < 0) {
		errno = EINVAL;
		return -1;
	}
	mdata = (U8 *)malloc(nbytes);
	if (!mdata) {
		errno = ENOMEM;
		return -1;
	}
	for (i = 0; i < nbytes; i += 8) {
		des_encrypt(&ctx, mdata + i, data + i);
	}
	memcpy(data, mdata, nbytes);
	free(mdata);
	return nbytes;
}

/**
 * @brief 用DES算法解密数据。
 * 
 * @param key 解密密钥（8字节）。
 * @param data 输入解密数据，输出解密结果。解密数据的长度必须是8的倍数。
 * @param nbytes 解密数据的长度。
 * 
 * @return 解密结果的长度，计算错误返回负数。
 */
S16 _des(const U8 key[8], U8 *data, const U16 nbytes)
{
	U16 i;
	U32 flags = 0;
	struct des_ctx ctx;
	U8 *mdata;
	
	if (!data) {
		errno = EBADF;
		return -1;
	}
	if (nbytes & 0x07) {
		errno = EINVAL;
		return -1;
	}
	if (des_setkey(&ctx, key, 8, &flags) < 0) {
		errno = EINVAL;
		return -1;
	}
	mdata = (U8 *)malloc(nbytes);
	if (!mdata) {
		errno = ENOMEM;
		return -1;
	}
	for (i = 0; i < nbytes; i += 8) {
		des_decrypt(&ctx, mdata + i, data + i);
	}
	memcpy(data, mdata, nbytes);
	free(mdata);
	return nbytes;
}

/**
 * @brief 用3DES算法加密数据。
 * 
 * @param key 加密密钥。
 * @param klen 加密密钥的长度。密钥长度只能是16或24。
 * @param data 输入加密数据，输出加密结果。加密数据的长度必须是8的倍数。
 * @param nbytes 加密数据的长度。
 * 
 * @return 加密结果的长度，计算错误返回负数。
 */
S16 des3(const U8 *key, const U16 klen, U8 *data, const U16 nbytes)
{
	U16 i;
	U32 flags = 0;
	U8 tkey[24];
	struct des3_ede_ctx ctx;
	U8 *mdata;
	
	if (!key || !data) {
		errno = EBADF;
		return -1;
	}
	if (nbytes & 0x07 || (klen != 16 && klen != 24)) {
		errno = EINVAL;
		return -1;
	}
	if (klen == 16) {
		memcpy(tkey, key, klen);
		memcpy(tkey + klen, key, 8);
	} else {
		memcpy(tkey, key, klen);
	}
	if (des3_ede_setkey(&ctx, tkey, 24, &flags) < 0) {
		errno = EINVAL;
		return -1;
	}
	mdata = (U8 *)malloc(nbytes);
	if (!mdata) {
		errno = ENOMEM;
		return -1;
	}
	for (i = 0; i < nbytes; i += 8) {
		des3_ede_encrypt(&ctx, mdata + i, data + i);
	}
	memcpy(data, mdata, nbytes);
	free(mdata);
	return nbytes;
}

/**
 * @brief 用3DES算法解密数据。
 * 
 * @param key 解密密钥。
 * @param klen 解密密钥的长度。密钥长度只能是16或24。
 * @param data 输入解密数据，输出解密结果。解密数据的长度必须是8的倍数。
 * @param nbytes 解密数据的长度。
 * 
 * @return 解密结果的长度，计算错误返回负数。
 */
S16 _des3(const U8 *key, const U16 klen, U8 *data, const U16 nbytes)
{
	U16 i;
	U32 flags = 0;
	U8 tkey[24];
	struct des3_ede_ctx ctx;
	U8 *mdata;
	
	if (!key || !data) {
		errno = EBADF;
		return -1;
	}
	if (nbytes & 0x07 || (klen != 16 && klen != 24)) {
		errno = EINVAL;
		return -1;
	}
	if (klen == 16) {
		memcpy(tkey, key, klen);
		memcpy(tkey + klen, key, 8);
	} else {
		memcpy(tkey, key, klen);
	}
	if (des3_ede_setkey(&ctx, tkey, 24, &flags) < 0) {
		errno = EINVAL;
		return -1;
	}
	mdata = (U8 *)malloc(nbytes);
	if (!mdata) {
		errno = ENOMEM;
		return -1;
	}
	for (i = 0; i < nbytes; i += 8) {
		des3_ede_decrypt(&ctx, mdata + i, data + i);
	}
	memcpy(data, mdata, nbytes);
	free(mdata);
	return nbytes;
}


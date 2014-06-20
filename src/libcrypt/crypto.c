/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file  crypto.c
 * @brief ���ü����㷨�ӿڡ�
 */
#include <string.h>
#include <stdlib.h>
#include "des.h"
#include "byteo.h"
#include "crypto.h"

/**
 * @brief ��DES�㷨�������ݡ�
 * 
 * @param key ������Կ��8�ֽڣ���
 * @param data ����������ݣ�������ܽ�����������ݵĳ��ȱ�����8�ı�����
 * @param nbytes �������ݵĳ��ȡ�
 * 
 * @return ���ܽ���ĳ��ȣ�������󷵻ظ�����
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
 * @brief ��DES�㷨�������ݡ�
 * 
 * @param key ������Կ��8�ֽڣ���
 * @param data ����������ݣ�������ܽ�����������ݵĳ��ȱ�����8�ı�����
 * @param nbytes �������ݵĳ��ȡ�
 * 
 * @return ���ܽ���ĳ��ȣ�������󷵻ظ�����
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
 * @brief ��3DES�㷨�������ݡ�
 * 
 * @param key ������Կ��
 * @param klen ������Կ�ĳ��ȡ���Կ����ֻ����16��24��
 * @param data ����������ݣ�������ܽ�����������ݵĳ��ȱ�����8�ı�����
 * @param nbytes �������ݵĳ��ȡ�
 * 
 * @return ���ܽ���ĳ��ȣ�������󷵻ظ�����
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
 * @brief ��3DES�㷨�������ݡ�
 * 
 * @param key ������Կ��
 * @param klen ������Կ�ĳ��ȡ���Կ����ֻ����16��24��
 * @param data ����������ݣ�������ܽ�����������ݵĳ��ȱ�����8�ı�����
 * @param nbytes �������ݵĳ��ȡ�
 * 
 * @return ���ܽ���ĳ��ȣ�������󷵻ظ�����
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


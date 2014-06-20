/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file  crypto.h
 * @brief 常用加密算法接口。
 */
#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include "types.h"

S16 des(const U8 key[8], U8 *data, const U16 nbytes);
S16 _des(const U8 key[8], U8 *data, const U16 nbytes);
S16 des3(const U8 *key, const U16 klen,U8 *data, const U16 nbytes);
S16 _des3(const U8 *key, const U16 klen, U8 *data, const U16 nbytes);

#endif /*__CRYPTO_H__*/


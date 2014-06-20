/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file  mac.h
 * @brief MAC算法库。
 */
#ifndef __MAC_H__
#define __MAC_H__

#include "types.h"

/** @brief MAC计算先异或再异或。 */
#define MAC_XOR_XOR   0x01
/** @brief MAC计算先异或再加密。 */
#define MAC_XOR_ENC   0x02
/** @brief MAC计算先加密再异或。 */
#define MAC_ENC_XOR   0x04
/** @brief MAC计算先加密再异或。 */
#define MAC_ENC_ENC   0x08
/** @brief MAC计算每块使用DES加密。 */
#define MAC_EACH_DES  0x10
/** @brief MAC计算每块使用3DES加密。 */
#define MAC_EACH_3DES 0x20
/** @brief MAC计算最后一块使用DES加密。 */
#define MAC_LAST_DES  0x40
/** @brief MAC计算最后一块使用3DES加密。 */
#define MAC_LAST_3DES 0x80

S16 mac_ansi_x99(U8 dest[8], const U8 key[8], const U8 *data, const U16 nbytes);
S16 mac_ansi_x919(U8 dest[8], const U8 key[16], const U8 *data, const U16 nbytes);
S16 mac_pboc_des(U8 dest[8], const U8 key[8], const U8 *data, const U16 nbytes);
S16 mac_pboc_3des(U8 dest[8], const U8 key[16], const U8 *data, const U16 nbytes);
S16 mac_mobile_pay(U8 dest[8], const U8 key[16], const U8 *data, const U16 nbytes);
S16 mac_union_pay(U8 dest[8], const U8 key[16], const U8 *data, const U16 nbytes);
S16 mac(U8 dest[8], const U8 *key, const U16 klen, const U8 iv[8], const U8 *data, const U16 nbytes, const U16 flags);

S16 mab_xor(U8 dest[8], const U8 *data, const U16 nbytes);
S16 mac_ck30(U8 dest[8], const U8 key[16], const U8 *data, const U16 nbytes, const U8 type);

#ifdef __cplusplus
}
#endif

#endif /*__MAC_H__*/

/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file types.h
 * @brief �����������͡�
 */
#ifndef __TYPES_H__
#define __TYPES_H__

#include <errno.h>

/* �������� */
#ifndef USHORT
typedef unsigned short USHORT;
#endif
#ifndef ushort
typedef USHORT ushort;
#endif

#ifndef ULONG
typedef unsigned long ULONG;
#endif
#ifndef ulong
typedef ULONG ulong;
#endif

#ifndef UINT
typedef unsigned int UINT;
#endif
#ifndef uint
typedef UINT uint;
#endif

#ifndef UCHAR
typedef unsigned char UCHAR;
#endif
#ifndef uchar
typedef UCHAR uchar;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif
#ifndef byte
typedef BYTE byte;
#endif

#ifndef U8
typedef unsigned char U8;
#endif
#ifndef u8
typedef U8 u8;
#endif

#ifndef U16
typedef unsigned short U16;
#endif
#ifndef u16
typedef U16 u16;
#endif

#ifndef U32
typedef unsigned long U32;
#endif
#ifndef u32
typedef U32 u32;
#endif

#ifndef S8
typedef char S8;
#endif
#ifndef s8
typedef S8 s8;
#endif

#ifndef S16
typedef short S16;
#endif
#ifndef s16
typedef S16 s16;
#endif

#ifndef S32
typedef long S32;
#endif
#ifndef s32
typedef S32 s32;
#endif

#ifndef BOOL
typedef int BOOL;
#endif
#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif

#ifndef bool
#define bool BOOL
#endif
#ifndef false
#define false (0)
#endif
#ifndef true
#define true (!false)
#endif

#ifndef NULL
#define NULL (0)
#endif
#ifndef null
#define null (0)
#endif

#ifndef __le32_to_cpu
#define __le32_to_cpu(x) ((u32)(x))
#endif
#ifndef __cpu_to_le32
#define __cpu_to_le32(x) ((u32)(x))
#endif
#ifndef msleep
#define msleep(x) sleep((x) / 1000)
#endif

/* WORD������ */
#define MAKEWORD(x, y) (int)((((int)(x)) & 0xffff) | ((((int)(y)) & 0xffff) << 16))
#define LOWORD(w) (int)(((int)(w)) & 0xffff)
#define HIWORD(w) (int)((((int)(w)) & 0xffff0000) >> 16)

/* ���ش���x�������8�ı�������ֵ */
#define RND8(x) ((((x) + 7) >> 3) << 3)

/* ��������Ԫ�ظ��� */
#define ARR_NUM(a) (sizeof((a)) / sizeof((a)[0]))

/* ����x��2��m�η���� */
#define MUL_M(x, m) ((x) << (m))

/* ����x��2��m�η���� */
#define DIV_M(x, m) ((x) >> (m))

/* ����x��2��m�η����� */
#define REM_M(x, m) ((x) - (((x) >> (m)) << (m)))

/* ����x��y���࣬yΪ2��m�η� */
#define REM_Y(x, y) ((x) & ((y) - 1))

/*���ض�ά�����Ԫ�ظ���*/
#define ARR2_NUM(a) (sizeof((a))/sizeof((a)[0][0]))

/*���ض�ά���������*/
#define ARR2_COL_NUM(a) (sizeof((a)[0])/sizeof((a)[0][0]))

/*���ض�ά���������*/
#define ARR2_ROW_NUM(a) (sizeof((a))/(sizeof((a)[0])))

/*���ض�ά����Ԫ������׵�ַ��ƫ����*/
#define ARR2_POS(a, i, j) ((i) * ARR2_COL_NUM((a)) + (j))

/* ���ؽṹ��ĳ����Ĵ�С */
#define FSIZE(type, field) sizeof(((type *)0)->field)

/* ���ؽṹ��ĳ�����ƫ�Ƶ�ַ */
#define FPOS(type, field) ((U32)&((type *)0)->field)

#endif /* __TYPES_H__ */


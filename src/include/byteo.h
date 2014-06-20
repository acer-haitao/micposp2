/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file  byteo.h
 * @brief �ַ�������������
 */
#ifndef __BYTEO_H__
#define __BYTEO_H__

#include "types.h"

/** @brief ת����ASC�ַ���(0-9 : ; < = > ?)��Χ�ڡ� */
#define ABC_NUM     0x01
/** @brief ��ͷ����䡣 */
#define ABC_FORE    0x02
/** @brief ��������档 */
#define ABC_FILL    0x04
/** @brief ��������ַ�������ַ�Ĭ��Ϊ'0'��ָ���˸ò�������������ַ�Ϊ�����ַ��� */
#define ABC_FCH     0x08

/** @brief ������ʾ��ÿ����ʾ16��ʮ���������� */
#define HDX_MUL     0x01
/** @brief ��ʾ�б�ǡ���ÿ�п�ͷ��ʾ��ǰ�е�һ��ʮ������������ʼ��ַ�� */
#define HDX_LNUM    0x02
/** @brief ��ʾ�б�ǡ���ÿ�ж�����ʾ��ǰ�е��кš� */
#define HDX_CNUM    0x04
/** @brief ��ʾASC�ַ�������ÿ��β����ʾ��ǰ�е�ASC�ַ����� */
#define HDX_ASC     0x08
/** @brief ���Ӷ���ַ��������ⲿ��ε��øú���ʱ�������������棬��ԭ�е��������������ַ����������˸ò���Ҫע�������������������� */
#define HDX_JOIN    0x10

S16 asc2bcdx(const S8 *asc_buf, const U16 asc_len, U8 *bcd_buf, const U16 bcd_len, const U8 flags, .../* const S8 fch */);
/**
 * @brief ת��ASC�ַ���ΪBCD���档
 * flagsΪ0��ת����ASC�ַ���(0-9 a-f A-F)��Χ�ڣ��ַ�������Ϊ��������β�����'0'�ַ�������������棩��
 * 
 * @param a ASC�ַ�����
 * @param b ASC�ַ������ȡ�
 * @param c BCD����ָ�롣
 * @param d BCD���泤�ȡ�
 * 
 * @return ת�����BCD���泤�ȣ�ת��ʧ�ܷ��ظ�����
 */
#define asc2bcd(a, b, c, d) asc2bcdx((a), (b), (c), (d), 0)
S16 bcd2ascx(const U8 *bcd_buf, const U16 bcd_len, S8 *asc_buf, const U16 asc_len, const U8 flags, .../* const S8 fch */);
/**
 * @brief ת��BCD����ΪASC�ַ�����
 * flagsΪ0��ת����ASC�ַ���(0-9 a-f A-F)��Χ�ڣ�����䡣
 * 
 * @param a BCD����ָ�롣
 * @param b BCD���泤�ȡ�
 * @param c ASC�ַ�����
 * @param d ASC�ַ������ȡ�
 * 
 * @return ת�����ASC�ַ������ȣ�ת��ʧ�ܷ��ظ�����
 */
#define bcd2asc(a, b, c, d) bcd2ascx((a), (b), (c), (d), 0)

S8 *atrim(S8 *str);
S8 *ltrim(S8 *str);
S8 *rtrim(S8 *str);
S8 *trim(S8 *str);

bool isbreak(const S8 c);
bool isdigits(const S8 *s, const U16 nbytes);
bool isxdigits(const S8 *s, const U16 nbytes);

void ands(U8 *dest, const U8 *b1, const U8 *b2, const U16 nbytes);
void ors(U8 *dest, const U8 *b1, const U8 *b2, const U16 nbytes);
void xors(U8 *dest, const U8 *b1, const U8 *b2, const U16 nbytes);
void nots(U8 *dest, const U8 *b1, const U16 nbytes);

S8 *hexdumpx(void *vbuf, const U16 nbytes, const U8 flags, .../* const U8 hdx_ind */);
/**
 * @brief ������ʽ�����ֽ�����ʮ���������ִ���
 * flagsΪ0��������ʾʮ���������ִ���
 *
 * @param a �����ֽ�����
 * @param b �����ֽ������ȡ�
 * 
 * @return ʮ���������ִ���������쳣���ؿա�
 */
#define hexdump(a, b) hexdumpx(a, (b), 0)
/**
 * @brief ������ʽ�����ֽ�����ʮ���������ִ���
 * flagsΪHDX_MUL | HDX_LNUM | HDX_CNUM | HDX_ASC����ʾ�б�Ǻ��б����֧�ֶ�����ʾ��ÿ����ʾ16���ֽڣ�ʮ���������ִ�������ĩ��ʾ��ǰ�е�asc�ַ���Ϣ��
 *
 * @param a �����ֽ�����
 * @param b �����ֽ������ȡ�
 * 
 * @return ʮ���������ִ���������쳣���ؿա�
 */
#define hexdump1(a, b) hexdumpx(a, (b), HDX_MUL | HDX_LNUM | HDX_CNUM | HDX_ASC)

#endif /*__BYTEO_H__*/


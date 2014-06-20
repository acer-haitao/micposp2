/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file  byteo.c
 * @brief �ַ�������������
 *
 * �����Ĺ��ܣ�
 *     @li��������ת������(asc2bcd | bcd2asc | bcd2int | int2bcd | asc2int | int2asc)��
 *     @li�ַ����ո�ضϺ���(trim | rtrim | ltrim | atrim)��
 *     @li�ַ�У�麯��(isbreak | isdigits)��
 *     @li�ֽ���λ���㺯��(ands | ors | xors | nots | reverse_bit | reverse_bits)��
 *     @liʮ���������������(hexdump)��
 */
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "byteo.h"

/**
 * @brief ת��ASC�ַ���ΪBCD���档
 * 
 * @param asc_buf ASC�ַ�����
 * @param asc_len ASC�ַ������ȡ�
 * @param bcd_buf BCD����ָ�롣
 * @param bcd_len BCD���泤�ȡ�
 * @param flags ת��������������(0 | ABC_NUM | ABC_FORE | ABC_FILL | ABC_FCH)�е���һֵ�����ֵ��
 *        ... fch ���ֵ�����ת������������ABC_FCH���������ø�ֵ����ֵ��ASC�ַ���(0-9 a-f A-F)��Χ�ڡ�
 * 
 * @return ת�����BCD���泤�ȣ�ת��ʧ�ܷ��ظ�����
 */
S16 asc2bcdx(const S8 *asc_buf, const U16 asc_len, U8 *bcd_buf, const U16 bcd_len, const U8 flags, .../* const S8 fch */)
{
	S8 fch = '0';
	S16 i, conv_len = 0;
	U8 ch, ch1, ch2;
	va_list ap;

	if (!asc_buf || !bcd_buf) {
		errno = EBADF;
		return -1;
	}
	//�ж�BCD�����Ƿ��㹻
	if ((bcd_len << 1) < asc_len) {
		errno = ENOMEM;
		return -1;
	}
	//�����Ҫָ������ַ�����ȡ������ַ�
	if (flags & ABC_FCH) {
		va_start(ap, flags);
		fch = va_arg(ap, int);
		va_end(ap);
	}
	//��ʽ���������
	if (fch >= 'a' && fch <= 'f') {
		ch2 = fch - 'a' + 10;
	} else if (fch >= 'A' && fch <= 'F') {
		ch2 = fch - 'A' + 10;
	} else if (fch >= '0' && fch <= '9') {
		ch2 = fch - '0';
	} else {
		errno = EINVAL;
		return -1;
	}
	ch2 |= ch2 << 4;
	//���Ҫ�����BCD���棬����������������������
	if (flags & ABC_FILL) {
		memset(bcd_buf, ch2, bcd_len);
	}
	//��ǰ�����ں����Ĳ�ͬ����
	ch1 = 0x55;
	if (flags & ABC_FORE) {
		if (flags & ABC_FILL) {
			bcd_buf += bcd_len - ((asc_len + 1) >> 1);
		}
		if (asc_len & 0x01) {
			ch1 = ch2 & 0x0F;
		}
	}
	//ת���ַ�
	for (i = 0; i < asc_len; asc_buf++, i++) {
		if (flags & ABC_NUM) {
			if (*asc_buf >= '0' && *asc_buf <= '?') {
				ch = *asc_buf - '0';
			} else {
				errno = EINVAL;
				return -1;
			}
		} else {
			if (*asc_buf >= 'a' && *asc_buf <= 'f') {
				ch = *asc_buf - 'a' + 10;
			} else if (*asc_buf >= 'A' && *asc_buf <= 'F') {
				ch = *asc_buf - 'A' + 10;
			} else if (*asc_buf >= '0' && *asc_buf <= '9') {
				ch = *asc_buf - '0';
			} else {
				errno = EINVAL;
				return -1;
			}
		}
		if (ch1 == 0x55) {
			ch1 = ch;
		} else {
			*bcd_buf++ = ch1 << 4 | ch;
			conv_len++;
			ch1 = 0x55;
		}
	}
	if (ch1 != 0x55) {
		*bcd_buf = ch1 << 4 | (ch2 & 0x0F);
		conv_len++;
	}
	if (flags & ABC_FILL) {
		return bcd_len;
	} else {
		return conv_len;
	}
}

/**
 * @brief ת��BCD����ΪASC�ַ�����
 * 
 * @param bcd_buf BCD����ָ�롣
 * @param bcd_len BCD���泤�ȡ�
 * @param asc_buf ASC�ַ�����
 * @param asc_len ASC�ַ������ȡ�
 * @param flags ת��������������(0, ABC_NUM, ABC_FORE, ABC_FILL, ABC_FCH)�е���һֵ�����ֵ��
 *        ... fch ���ֵ�����ת������������ABC_FCH���������ø�ֵ����ֵ��ASC�ַ���(0-9 a-f A-F)��Χ�ڡ�
 * 
 * @return ת�����ASC�ַ������ȣ�ת��ʧ�ܷ��ظ�����
 */
S16 bcd2ascx(const U8 *bcd_buf, const U16 bcd_len, S8 *asc_buf, const U16 asc_len, const U8 flags, .../* const S8 fch */)
{
	S8 fch = '0';
	S16 i = 0, j, conv_len;
	U8 ch1, ch2;
	va_list ap;
	
	if (!asc_buf || !bcd_buf) {
		errno = EBADF;
		return -1;
	}
	//�����Ҫָ������ַ�����ȡ������ַ�
	if (flags & ABC_FCH) {
		va_start(ap, flags);
		fch = va_arg(ap, int);
		va_end(ap);
	}
	//��ʽ���������
	if (fch >= 'a' && fch <= 'f') {
		ch2 = fch - 'a' + 10;
	} else if (fch >= 'A' && fch <= 'F') {
		ch2 = fch - 'A' + 10;
	} else if (fch >= '0' && fch <= '9') {
		ch2 = fch - '0';
	} else {
		errno = EINVAL;
		return -1;
	}
	ch2 |= ch2 << 4;
	//����ʵ��ת������ʼλ�ú����ݳ���
	conv_len = bcd_len << 1;
	if (flags & ABC_FILL) {
		if (flags & ABC_FORE) {
			while (conv_len > 0 && *bcd_buf == ch2) {
				bcd_buf++;
				conv_len -= 2;
			}
			if ((*bcd_buf & 0xf0) == (ch2 & 0xf0)) {
				i = 1;
				conv_len --;
			}
		} else {
			while (conv_len > 0 && *(bcd_buf + (conv_len >> 1) - 1) == ch2) {
				conv_len -= 2;
			}
			if ((*(bcd_buf + (conv_len >> 1) - 1) & 0x0f) == (ch2 & 0x0f)) {
				conv_len --;
			}
		}
	}
	//�ж�ASC�����Ƿ��㹻
	if (conv_len > asc_len) {
		errno = ENOMEM;
		return -1;
	}
	//ת���ַ�
	j = conv_len + i;
	for ( ; i < j; i++, asc_buf++) {
		ch1 = (i & 0x01) ? (*bcd_buf++ & 0x0f) : (*bcd_buf >> 4);
		if (flags & ABC_NUM) {
			ch1 += '0';
		} else {
			ch1 += (ch1 > 9) ? ('A' - 10) : '0';
		}
		*asc_buf = ch1;
	}
	return conv_len;
}

/**
 * @brief �ض��ַ�����ȫ���ո񣨰����ַ����м䣩��
 * 
 * @param str �����ַ�����
 * 
 * @return �ضϺ���ַ���ָ�롣
 */
S8 *atrim(S8 *str)
{
	S8 *p, *q;
	p = q = str;
	while (*p) {
		if (!isspace(*p)) {
			*q++ = *p;
		}
		p++;
	}
	*q = '\0';
	return str;
}

/**
 * @brief �ض��ַ�������ո�
 * 
 * @param str �����ַ�����
 * 
 * @return �ضϺ���ַ���ָ�롣
 */
S8 *ltrim(S8 *str)
{
	while (*str && isspace(*str)) str++;
	return str;
}

/**
 * @brief �ض��ַ������ҿո�
 * 
 * @param str �����ַ�����
 * 
 * @return �ضϺ���ַ���ָ�롣
 */
S8 *rtrim(S8 *str)
{
	S8 *p;
	p = str + strlen(str) - 1;
	while (p > str && isspace(*p)) {
		*p = '\0';
		p--;
	}
	return str;
}

/**
 * @brief �ض��ַ��������ҿո�
 * 
 * @param str �����ַ�����
 * 
 * @return �ضϺ���ַ���ָ�롣
 */
S8 *trim(S8 *str)
{
	S8 *p;
	p = ltrim(str);
	p = rtrim(p);
	return p;
}

/**
 * @brief ����ַ��Ƿ��ǻ��з���'\r','\n'����
 * 
 * @param c �����ַ���
 * 
 * @return true��false��
 */
bool isbreak(const S8 c)
{
	return ((c) == '\r' || (c) == '\n') ? true: false;
}

/**
 * @brief ����ַ����Ƿ�ȫ�������ַ���0-9����
 * 
 * @param s �����ַ�����
 * @param nbytes �����ַ������ȡ�
 * 
 * @return true��false��
 */
bool isdigits(const S8 *s, const U16 nbytes)
{
	S16 i;
	for (i = 0; i < nbytes; i++, s++) {
		if (!isdigit(*s))
			return false;
	}
	return true;
}

/**
 * @brief ����ַ����Ƿ�ȫ��ʮ�������ַ���0-9��a-f����
 * 
 * @param s �����ַ�����
 * @param nbytes �����ַ������ȡ�
 * 
 * @return true��false��
 */
bool isxdigits(const S8 *s, const U16 nbytes)
{
	S16 i;
	for (i = 0; i < nbytes; i++, s++) {
		if (!isxdigit(*s))
			return false;
	}
	return true;
}

/**
 * @brief ���ֽ����롣
 * 
 * @param dest ������档
 * @param b1 ����1���档
 * @param b2 ����2���档
 * @param nbytes ���뻺���С��
 */
void ands(U8 *dest, const U8 *b1, const U8 *b2, const U16 nbytes)
{
	S16 i;
	for (i = 0; i < nbytes; i++) {
		*dest++ = *b1++ & *b2++;
	}
}

/**
 * @brief ���ֽ����
 * 
 * @param dest ������档
 * @param b1 ����1���档
 * @param b2 ����2���档
 * @param nbytes ���뻺���С��
 */
void ors(U8 *dest, const U8 *b1, const U8 *b2, const U16 nbytes)
{
	S16 i;
	for (i = 0; i < nbytes; i++) {
		*dest++ = *b1++ | *b2++;
	}
}

/**
 * @brief ���ֽ������
 * 
 * @param dest ������档
 * @param b1 ����1���档
 * @param b2 ����2���档
 * @param nbytes ���뻺���С��
 */
void xors(U8 *dest, const U8 *b1, const U8 *b2, const U16 nbytes)
{
	S16 i;
	for (i = 0; i < nbytes; i++) {
		*dest++ = *b1++ ^ *b2++;
	}
}

/**
 * @brief ���ֽ������
 * 
 * @param dest ������档
 * @param b1 ���뻺�档
 * @param nbytes ���뻺���С��
 */
void nots(U8 *dest, const U8 *b1, const U16 nbytes)
{
	S16 i;
	for (i = 0; i < nbytes; i++) {
		*dest++ = ~*b1++;
	}
}

#define HEXDUMP_SIZE (1024 * 20)
S8 hexdump_buf[HEXDUMP_SIZE + 1];

S8 *strcpyx(S8 *p, const S8 *s)
{
	S16 l;
	strcpy(p, s);
	l = strlen(s);
	p += l;
	return p;
}

S8 *sprintfx(S8 *p, const S8 *s, ...)
{
	S16 l;
	va_list args;

	va_start(args, s);
	vsprintf(p, s, args);
	va_end(args);
	l = strlen(p);
	p += l;
	return p;
}

/**
 * @brief ����ָ������ʽ�����ֽ�����ʮ���������ִ���
 * 
 * @param buf �����ֽ�����
 * @param nbytes �����ֽ������ȡ�
 * @param flags ��ʽ������������(0, HDX_MUL, HDX_LNUM, HDX_CNUM, HDX_ASC, HDX_JOIN)�е���һֵ�����ֵ��
 * @param ... ���������������ʽ����������HDX_JOIN���������ø�ֵ����ֵΪ0-255������
 *  		  ע�⣺printf��sprintf�Ⱥ����ĵ����������ǴӺ���ǰȡֵ������˳��Ҳ����Ӻ���ǰ������
 *  		  �磺printf("%s%s", hexdumpx(buf, len, HDX_JOIN,
 *  		  1), hexdumpx(buf, len, HDX_JOIN, 0));
 * 
 * @return ʮ���������ִ���������쳣���ؿա�
 */
S8 *hexdumpx(void *vbuf, const U16 nbytes, const U8 flags, .../* const U8 hdx_ind */)
{
	S16 i, j;
	U8 hdx_ind;
	S8 *s, *e, *p, *sz = NULL, *psz = NULL;
	va_list ap;
	U8 *buf = (U8 *)vbuf;
	
	if (flags & HDX_ASC) {
		sz = (S8 *)malloc(nbytes * sizeof(S8) + 1);
		if (!sz)
			return NULL;
		psz = sz;
	}
	s = hexdump_buf;
	e = hexdump_buf + sizeof(hexdump_buf);
	if (flags & HDX_JOIN) {
		va_start(ap, flags);
		hdx_ind = va_arg(ap, int);
		va_end(ap);
		while (hdx_ind--) {
			s += strlen(s) + 1;
			if (s > e) return NULL;
		}
	}
	*s = '\0';
	p = s;
	
	if (flags & HDX_CNUM) {
		if (flags & HDX_LNUM) {
			p = strcpyx(p, "           ");
		}
		p = strcpyx(p, "0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  \n");
		if (flags & HDX_LNUM) {
			p = strcpyx(p, "-----------");
		}
		p = strcpyx(p, "------------------------------------------------------------------\n");
	}
	
	for (i = 0; i < nbytes; buf++, i++) {
		if (flags & HDX_LNUM) {
			if (i == 0 || ((flags & HDX_MUL) && !(i & 0x0f))) {
				p = sprintfx(p, "%08Xh: ", buf);
			}
		}
		p = sprintfx(p, "%02X ", *buf);
		if ((flags & HDX_ASC)) {
			if (*buf == '\0' || isspace(*buf)) {
				*psz++ = '.';
			} else {
				*psz++ = *buf;
			}
			if (i == nbytes - 1 || ((flags & HDX_MUL) && !((i & 0x0f) ^ 0x0f))) {
				if (flags & HDX_MUL) {
					for (j = 0; j < ((i & 0x0f) ^ 0x0f); j++)
						p = strcpyx(p, "   ");
				}
				*psz = '\0';
				p = sprintfx(p, ";%s", sz);
				psz = sz;
			}
		}
		if (i == nbytes - 1 || ((flags & HDX_MUL) && !((i & 0x0f) ^ 0x0f))) {
			p = strcpyx(p, "\n");
		}
	}
	if (flags & HDX_CNUM) {
		if (flags & HDX_LNUM) {
			p = strcpyx(p, "-----------");
		}
		p = strcpyx(p, "------------------------------------------------------------------\n");
	}
	if ((flags & HDX_ASC) && sz) {
		free(sz);
	}
	return s;
}


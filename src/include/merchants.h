/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file merchants.h
 * @brief 商户信息库。
 */
#ifndef __MERCHANTS_H__
#define __MERCHANTS_H__

#define MID_SIZE 15
#define TID_SIZE 8
#define MNAME_MAXSIZE 200
#define MMENU_MAXSIZE 80

typedef struct _merchants_s MERCHANTS;
struct _merchants_s {
	char mid[MID_SIZE + 1];
	char tid[TID_SIZE + 1];
	char mname[MNAME_MAXSIZE + 1];
	char mmenu[MMENU_MAXSIZE + 1];
};

int do_sel_merchants(int param);
int do_add_merchants(int param);
int do_update_merchants(int param);
int do_del_merchants(int param);

#endif /*__MERCHANTS_H__*/


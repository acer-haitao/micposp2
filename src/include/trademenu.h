/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file trademenu.h
 * @brief 交易菜单信息库。
 */
#ifndef __TRADEMENU_H__
#define __TRADEMENU_H__

#define TMID_SIZE 4
#define TMNAME_MAXSIZE 20
#define TMTYPE_SIZE 1
#define TMDESC_MAXSIZE 200
#define TMTC_SIZE 3

typedef struct _trademenu_s TRADEMENU;
struct _trademenu_s {
	char tmid[TMID_SIZE + 1];
	char tmname[TMNAME_MAXSIZE + 1];
	char tmtype[TMTYPE_SIZE + 1];
	char tmdesc[TMDESC_MAXSIZE + 1];
	char tmtc[TMTC_SIZE + 1];
};

int do_sel_trademenu(int param);
int do_add_trademenu(int param);
int do_update_trademenu(int param);
int do_del_trademenu(int param);

#endif /*__TRADEMENU_H__*/


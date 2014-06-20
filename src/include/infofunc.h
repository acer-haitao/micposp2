/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file types.h
 * @brief 基本数据类型。
 */
#ifndef __INFOFUNC_H__
#define __INFOFUNC_H__

typedef enum {
	IT_MERCHANTS,
	IT_TRADEMENU,
	IT_TRADEFLOW
}INFO_TYPE;

typedef enum {
	IO_SEL,
	IO_ADD,
	IO_UPDATE,
	IO_DEL
}INFO_OP;

#define INFO_MAXINPUT 255

int do_op_info(int param);
bool sel_db(INFO_TYPE type, char *pid, int count, ...);
bool add_db(INFO_TYPE type, int count, ...);
bool update_db(INFO_TYPE type, char *pid, int count, ...);
bool del_db(INFO_TYPE type, char *pid);

#endif /*__INFOFUNC_H__*/


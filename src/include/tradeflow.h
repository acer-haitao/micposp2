/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file tradeflow.h
 * @brief 交易流程信息库。
 */
#ifndef __TRADEFLOW_H__
#define __TRADEFLOW_H__

#define TFTC_SIZE 3
#define TFDESC_MAXSIZE 200
#define TFFC_MAXSIZE 50

typedef struct _tradeflow_s TRADEFLOW;
struct _tradeflow_s {
	char tftc[TFTC_SIZE + 1];
	char tfdesc[TFDESC_MAXSIZE + 1];
	char tffc[TFFC_MAXSIZE + 1];
};

int do_sel_tradeflow(int param);
int do_add_tradeflow(int param);
int do_update_tradeflow(int param);
int do_del_tradeflow(int param);

#endif /*__TRADEFLOW_H__*/


/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file  sysadmin.h
 * @brief 系统管理功能。
 */
#ifndef __SYSADMIN_H__
#define __SYSADMIN_H__

bool sys_init();
int do_sys_recover(int param);
int do_sys_backup(int param);

#endif /*__SYSADMIN_H__*/


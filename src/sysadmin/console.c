/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file console.c
 * @brief 人机交互控制台。
 */
#include "all.h"
#include "tradekey.h"
#include "sysfunc.h"
#include "infofunc.h"
#include "console.h"

/* @brief 菜单标题最大长度 */
#define MENU_TITLE_MAXSIZE 20
/* @brief 系统标题 */
#define SYS_TITLE "#### POS业务数据管理系统 ####"

/* @brief 控制台操作菜单结构 */
typedef struct _menu_s MENU;
struct _menu_s {
	char title[MENU_TITLE_MAXSIZE + 1];
	const MENU* cmenu;
	int cmenu_num;
	fun_do_proc proc;
	int param;
};

typedef struct _menu_list_s MENU_LIST;
struct _menu_list_s {
	char title[MENU_TITLE_MAXSIZE + 1];
	MENU *menus;
	int num;
	int param;
	MENU_LIST *next;
};

#define MAIN_MENU_NUM 6
extern const MENU main_menu[MAIN_MENU_NUM];
#define SYSADMIN_MENU_NUM 3
extern const MENU sysadmin_menu[SYSADMIN_MENU_NUM];
#define INFOADMIN_MENU_NUM 5
extern const MENU infoadmin_menu[INFOADMIN_MENU_NUM];
#define KEYADMIN_MENU_NUM 2
extern const MENU keyadmin_menu[KEYADMIN_MENU_NUM];

MENU_LIST *pop(MENU_LIST *top);
MENU_LIST *push(MENU_LIST *top, MENU_LIST *p);
void show_menu(MENU_LIST *p);

/* 菜单数据 */
const MENU main_menu[] = {
	{"系统管理", sysadmin_menu, SYSADMIN_MENU_NUM, NULL, 0},
	{"商户管理", infoadmin_menu, INFOADMIN_MENU_NUM, NULL, IT_MERCHANTS},
	{"交易菜单管理", infoadmin_menu, INFOADMIN_MENU_NUM, NULL, IT_TRADEMENU},
	{"交易流程管理", infoadmin_menu, INFOADMIN_MENU_NUM, NULL, IT_TRADEFLOW},
	{"交易密钥管理", keyadmin_menu, KEYADMIN_MENU_NUM, NULL, 0},
	{"退出", NULL, 0, NULL, 0}
};

const MENU sysadmin_menu[] = {
	{"系统备份", NULL, 0, do_sys_backup, 0},
	{"系统恢复", NULL, 0, do_sys_recover, 0},
	{"返回", NULL, 0, NULL, 0}
};

const MENU infoadmin_menu[] = {
	{"查询数据", NULL, 0, do_op_info, IO_SEL},
	{"添加数据", NULL, 0, do_op_info, IO_ADD},
	{"修改数据", NULL, 0, do_op_info, IO_UPDATE},
	{"删除数据", NULL, 0, do_op_info, IO_DEL},
	{"返回", NULL, 0, NULL, 0}
};

const MENU keyadmin_menu[] = {
	{"更新密钥", NULL, 0, do_update_key, 0},
	{"返回", NULL, 0, NULL, 0}
};

MENU_LIST *pop(MENU_LIST *top)
{
	top = top->next;
	return top;
}

MENU_LIST *push(MENU_LIST *top, MENU_LIST *p)
{
	p->next = top;
	top = p;
	return top;
}

void console()
{
	MENU_LIST *top, *p;
	int sel;
	MENU *sel_menu;

	LOG(LOG_DEBUG, "加载主菜单...");
	top = NULL;
	while (1) {
		if (!top || sel_menu) {
			//创建新的菜单列表
			p = (MENU_LIST *)calloc(sizeof(MENU_LIST), 1);
			if (!p) {
				LOG(LOG_ERROR, "创建新的菜单列表失败！");
				return;
			}
			if (!top) {
				strcpy(p->title, "主菜单");
				p->menus = (MENU *)main_menu;
				p->num = MAIN_MENU_NUM;
			} else {
				strcpy(p->title, sel_menu->title);
				p->menus = (MENU *)sel_menu->cmenu;
				p->num = sel_menu->cmenu_num;
				p->param = sel_menu->param;
			}
			top = push(top, p);
		}
		//清空菜单选择项
		sel = 0;
		sel_menu = NULL;
		//加载菜单
		show_menu(top);
		printf("请选择菜单：");
		scanf("%d", &sel);
		getchar();
		LOG(LOG_DEBUG, "选择菜单[%d]...", sel);
		if (sel > top->num || sel <= 0) {
			printf("选择的菜单无效，请重新选择！\n");
			LOG(LOG_ERROR, "选择的菜单无效，请重新选择！");
			continue;
		}
		//每个菜单最后一个菜单项为退出或返回功能
		if (sel == top->num) {
			p = top;
			top = pop(top);
			free(p);
			if (!top) {
				break;
			} else {
				continue;
			}
		}
		//设置当前选择菜单项
		sel_menu = &top->menus[sel - 1];
		//根据菜单执行功能或加载子菜单
		if (sel_menu->proc) {
			LOG(LOG_DEBUG, "执行菜单[%d]功能...", sel);
			(*sel_menu->proc)(MAKEWORD(top->param, sel_menu->param));
			sel_menu = NULL;
		} else if (sel_menu->cmenu) {
			LOG(LOG_DEBUG, "加载菜单[%d]的子菜单...", sel);
		} else {
			sel_menu = NULL;
			printf("选择的菜单无效，请重新选择！\n");
			LOG(LOG_DEBUG, "选择的菜单无效，请重新选择！");
		}
	}
}

void show_menu(MENU_LIST *p)
{
	int i;

	printf("\n%s\n", SYS_TITLE);
	printf("    %s\n", p->title);
	printf("--------------------\n");
	for (i = 0; i < p->num; i++) {
		printf("[%d] %s\n", i + 1, p->menus[i].title);
	}
}


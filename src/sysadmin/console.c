/**
 * Copyright(c) 2011, Free software organization.
 * All Rights Reserved.
 * 
 * @author kezf<kezf@foxmail.com>
 * @file console.c
 * @brief �˻���������̨��
 */
#include "all.h"
#include "tradekey.h"
#include "sysfunc.h"
#include "infofunc.h"
#include "console.h"

/* @brief �˵�������󳤶� */
#define MENU_TITLE_MAXSIZE 20
/* @brief ϵͳ���� */
#define SYS_TITLE "#### POSҵ�����ݹ���ϵͳ ####"

/* @brief ����̨�����˵��ṹ */
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

/* �˵����� */
const MENU main_menu[] = {
	{"ϵͳ����", sysadmin_menu, SYSADMIN_MENU_NUM, NULL, 0},
	{"�̻�����", infoadmin_menu, INFOADMIN_MENU_NUM, NULL, IT_MERCHANTS},
	{"���ײ˵�����", infoadmin_menu, INFOADMIN_MENU_NUM, NULL, IT_TRADEMENU},
	{"�������̹���", infoadmin_menu, INFOADMIN_MENU_NUM, NULL, IT_TRADEFLOW},
	{"������Կ����", keyadmin_menu, KEYADMIN_MENU_NUM, NULL, 0},
	{"�˳�", NULL, 0, NULL, 0}
};

const MENU sysadmin_menu[] = {
	{"ϵͳ����", NULL, 0, do_sys_backup, 0},
	{"ϵͳ�ָ�", NULL, 0, do_sys_recover, 0},
	{"����", NULL, 0, NULL, 0}
};

const MENU infoadmin_menu[] = {
	{"��ѯ����", NULL, 0, do_op_info, IO_SEL},
	{"�������", NULL, 0, do_op_info, IO_ADD},
	{"�޸�����", NULL, 0, do_op_info, IO_UPDATE},
	{"ɾ������", NULL, 0, do_op_info, IO_DEL},
	{"����", NULL, 0, NULL, 0}
};

const MENU keyadmin_menu[] = {
	{"������Կ", NULL, 0, do_update_key, 0},
	{"����", NULL, 0, NULL, 0}
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

	LOG(LOG_DEBUG, "�������˵�...");
	top = NULL;
	while (1) {
		if (!top || sel_menu) {
			//�����µĲ˵��б�
			p = (MENU_LIST *)calloc(sizeof(MENU_LIST), 1);
			if (!p) {
				LOG(LOG_ERROR, "�����µĲ˵��б�ʧ�ܣ�");
				return;
			}
			if (!top) {
				strcpy(p->title, "���˵�");
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
		//��ղ˵�ѡ����
		sel = 0;
		sel_menu = NULL;
		//���ز˵�
		show_menu(top);
		printf("��ѡ��˵���");
		scanf("%d", &sel);
		getchar();
		LOG(LOG_DEBUG, "ѡ��˵�[%d]...", sel);
		if (sel > top->num || sel <= 0) {
			printf("ѡ��Ĳ˵���Ч��������ѡ��\n");
			LOG(LOG_ERROR, "ѡ��Ĳ˵���Ч��������ѡ��");
			continue;
		}
		//ÿ���˵����һ���˵���Ϊ�˳��򷵻ع���
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
		//���õ�ǰѡ��˵���
		sel_menu = &top->menus[sel - 1];
		//���ݲ˵�ִ�й��ܻ�����Ӳ˵�
		if (sel_menu->proc) {
			LOG(LOG_DEBUG, "ִ�в˵�[%d]����...", sel);
			(*sel_menu->proc)(MAKEWORD(top->param, sel_menu->param));
			sel_menu = NULL;
		} else if (sel_menu->cmenu) {
			LOG(LOG_DEBUG, "���ز˵�[%d]���Ӳ˵�...", sel);
		} else {
			sel_menu = NULL;
			printf("ѡ��Ĳ˵���Ч��������ѡ��\n");
			LOG(LOG_DEBUG, "ѡ��Ĳ˵���Ч��������ѡ��");
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


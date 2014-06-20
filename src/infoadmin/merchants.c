#include "all.h"
#include "infofunc.h"
#include "merchants.h"

#define MEMBERS_COUNT 4

int do_sel_merchants(int param)
{
	int c;
	MERCHANTS merchants;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行查询商户信息功能...");
	memset(&merchants, 0, sizeof(merchants));
INPUT_MID:
	printf("请输入[查询]的商户编号：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != MID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", MID_SIZE);
		goto INPUT_MID;
	}
	if (!sel_db(IT_MERCHANTS, tmp, MEMBERS_COUNT, merchants.mid, merchants.tid, merchants.mname, merchants.mmenu)) {
		printf("查询商户：%s失败！\n", tmp);
		return -1;
	} else {
		printf("查询商户：%s成功。\n", tmp);
		printf("商户编号：%s\n", merchants.mid);
		printf("终端编号：%s\n", merchants.tid);
		printf("商户名称：%s\n", merchants.mname);
		printf("商户菜单：%s\n", merchants.mmenu);
		return 0;
	}
}

int do_add_merchants(int param)
{
	int c;
	MERCHANTS merchants;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行添加商户信息功能...");
	memset(&merchants, 0, sizeof(merchants));
INPUT_MID:
	printf("请输入[添加]商户编号：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != MID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", MID_SIZE);
		goto INPUT_MID;
	}
	memcpy(merchants.mid, tmp, strlen(tmp));
INPUT_TID:
	printf("请输入终端编号：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TID_SIZE);
		goto INPUT_TID;
	}
	memcpy(merchants.tid, tmp, strlen(tmp));
INPUT_MNAME:
	printf("请输入商户名称：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > MNAME_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", MNAME_MAXSIZE);
		goto INPUT_MNAME;
	}
	memcpy(merchants.mname, tmp, strlen(tmp));
INPUT_MMENU:
	printf("请输入商户菜单：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > MMENU_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", MMENU_MAXSIZE);
		goto INPUT_MMENU;
	}
	memcpy(merchants.mmenu, tmp, strlen(tmp));
	if (sel_db(IT_MERCHANTS, merchants.mid, 0)) {
		printf("添加商户：%s失败，商户已经存在！\n", merchants.mid);
		return -1;
	}
	if (!add_db(IT_MERCHANTS, MEMBERS_COUNT, merchants.mid, merchants.tid, merchants.mname, merchants.mmenu)) {
		printf("添加商户：%s失败！\n", merchants.mid);
		return -1;
	} else {
		printf("添加商户：%s成功。\n", merchants.mid);
		return 0;
	}
}

int do_update_merchants(int param)
{
	int c;
	MERCHANTS merchants;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行修改商户信息功能...");
	memset(&merchants, 0, sizeof(merchants));
INPUT_MID:
	printf("请输入[修改]商户编号：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != MID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", MID_SIZE);
		goto INPUT_MID;
	}
	memcpy(merchants.mid, tmp, strlen(tmp));
INPUT_TID:
	printf("请输入终端编号：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TID_SIZE);
		goto INPUT_TID;
	}
	memcpy(merchants.tid, tmp, strlen(tmp));
INPUT_MNAME:
	printf("请输入商户名称：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > MNAME_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", MNAME_MAXSIZE);
		goto INPUT_MNAME;
	}
	memcpy(merchants.mname, tmp, strlen(tmp));
INPUT_MMENU:
	printf("请输入商户菜单：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > MMENU_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", MMENU_MAXSIZE);
		goto INPUT_MMENU;
	}
	memcpy(merchants.mmenu, tmp, strlen(tmp));
	if (!update_db(IT_MERCHANTS, merchants.mid, MEMBERS_COUNT, merchants.mid, merchants.tid, merchants.mname, merchants.mmenu)) {
		printf("修改商户：%s失败！\n", merchants.mid);
		return -1;
	} else {
		printf("修改商户：%s成功。\n", merchants.mid);
		return 0;
	}
}

int do_del_merchants(int param)
{
	int c;
	MERCHANTS merchants;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行删除商户信息功能...");
	memset(&merchants, 0, sizeof(merchants));
INPUT_MID:
	printf("请输入[删除]的商户编号：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != MID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", MID_SIZE);
		goto INPUT_MID;
	}
	if (!del_db(IT_MERCHANTS, tmp)) {
		printf("删除商户：%s失败！\n", tmp);
		return -1;
	} else {
		printf("删除商户：%s成功。\n", tmp);
		return 0;
	}
}


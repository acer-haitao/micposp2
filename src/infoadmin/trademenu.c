#include "all.h"
#include "infofunc.h"
#include "trademenu.h"

#define MEMBERS_COUNT 5

int do_sel_trademenu(int param)
{
	int c;
	TRADEMENU trademenu;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行查询交易菜单信息功能...");
	memset(&trademenu, 0, sizeof(trademenu));
INPUT_TMID:
	printf("请输入[查询]的交易菜单编号：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TMID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TMID_SIZE);
		goto INPUT_TMID;
	}
	if (!sel_db(IT_TRADEMENU, tmp, MEMBERS_COUNT, trademenu.tmid, trademenu.tmname, trademenu.tmtype, trademenu.tmdesc, trademenu.tmtc)) {
		printf("查询交易菜单：%s失败！\n", tmp);
		return -1;
	} else {
		printf("查询交易菜单：%s成功。\n", tmp);
		printf("交易菜单编号：%s\n", trademenu.tmid);
		printf("交易菜单名称：%s\n", trademenu.tmname);
		printf("交易菜单类型：%s\n", trademenu.tmtype);
		printf("交易菜单说明：%s\n", trademenu.tmdesc);
		printf("交易代码：%s\n", trademenu.tmtc);
		return 0;
	}
}

int do_add_trademenu(int param)
{
	int c;
	TRADEMENU trademenu;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行添加交易菜单信息功能...");
	memset(&trademenu, 0, sizeof(trademenu));
INPUT_TMID:
	printf("请输入交易菜单编号：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TMID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TMID_SIZE);
		goto INPUT_TMID;
	}
	memcpy(trademenu.tmid, tmp, strlen(tmp));
INPUT_TMNAME:
	printf("请输入交易菜单名称：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > TMNAME_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", TMNAME_MAXSIZE);
		goto INPUT_TMNAME;
	}
	memcpy(trademenu.tmname, tmp, strlen(tmp));
INPUT_TMTYPE:
	printf("请输入交易菜单类型：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TMTYPE_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TMTYPE_SIZE);
		goto INPUT_TMTYPE;
	}
	memcpy(trademenu.tmtype, tmp, strlen(tmp));
INPUT_TMDESC:
	printf("请输入交易菜单说明：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > TMDESC_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", TMDESC_MAXSIZE);
		goto INPUT_TMDESC;
	}
	memcpy(trademenu.tmdesc, tmp, strlen(tmp));
INPUT_TMTC:
	printf("请输入交易代码：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TMTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TMTC_SIZE);
		goto INPUT_TMTC;
	}
	memcpy(trademenu.tmtc, tmp, strlen(tmp));
	if (sel_db(IT_TRADEMENU, trademenu.tmid, 0)) {
		printf("添加交易菜单：%s失败，交易菜单已经存在！\n", trademenu.tmid);
		return -1;
	}
	if (!add_db(IT_TRADEMENU, MEMBERS_COUNT, trademenu.tmid, trademenu.tmname, trademenu.tmtype, trademenu.tmdesc, trademenu.tmtc)) {
		printf("添加交易菜单：%s失败！\n", trademenu.tmid);
		return -1;
	} else {
		printf("添加交易菜单：%s成功。\n", trademenu.tmid);
		return 0;
	}
}

int do_update_trademenu(int param)
{
	int c;
	TRADEMENU trademenu;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行修改交易菜单信息功能...");
	memset(&trademenu, 0, sizeof(trademenu));
INPUT_TMID:
	printf("请输入[修改]交易菜单编号：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TMID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TMID_SIZE);
		goto INPUT_TMID;
	}
	memcpy(trademenu.tmid, tmp, strlen(tmp));
INPUT_TMNAME:
	printf("请输入交易菜单名称：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > TMNAME_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", TMNAME_MAXSIZE);
		goto INPUT_TMNAME;
	}
	memcpy(trademenu.tmname, tmp, strlen(tmp));
INPUT_TMTYPE:
	printf("请输入交易菜单类型：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TMTYPE_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TMTYPE_SIZE);
		goto INPUT_TMTYPE;
	}
	memcpy(trademenu.tmtype, tmp, strlen(tmp));
INPUT_TMDESC:
	printf("请输入交易菜单说明：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > TMDESC_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", TMDESC_MAXSIZE);
		goto INPUT_TMDESC;
	}
	memcpy(trademenu.tmdesc, tmp, strlen(tmp));
INPUT_TMTC:
	printf("请输入交易代码：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TMTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TMTC_SIZE);
		goto INPUT_TMTC;
	}
	memcpy(trademenu.tmtc, tmp, strlen(tmp));
	if (!update_db(IT_TRADEMENU, trademenu.tmid, MEMBERS_COUNT, trademenu.tmid, trademenu.tmname, trademenu.tmtype, trademenu.tmdesc, trademenu.tmtc)) {
		printf("修改交易菜单：%s失败！\n", trademenu.tmid);
		return -1;
	} else {
		printf("修改交易菜单：%s成功。\n", trademenu.tmid);
		return 0;
	}
}

int do_del_trademenu(int param)
{
	int c;
	TRADEMENU trademenu;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行删除交易菜单信息功能...");
	memset(&trademenu, 0, sizeof(trademenu));
INPUT_TMID:
	printf("请输入[删除]的交易菜单编号：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TMID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TMID_SIZE);
		goto INPUT_TMID;
	}
	if (!del_db(IT_TRADEMENU, tmp)) {
		printf("删除交易菜单：%s失败！\n", tmp);
		return -1;
	} else {
		printf("删除交易菜单：%s成功。\n", tmp);
		return 0;
	}
}


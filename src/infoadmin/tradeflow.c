#include "all.h"
#include "infofunc.h"
#include "tradeflow.h"

#define MEMBERS_COUNT 3

int do_sel_tradeflow(int param)
{
	int c;
	TRADEFLOW tradeflow;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行查询交易流程信息功能...");
	memset(&tradeflow, 0, sizeof(tradeflow));
INPUT_TFTC:
	printf("请输入[查询]的交易代码：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TFTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TFTC_SIZE);
		goto INPUT_TFTC;
	}
	if (!sel_db(IT_TRADEFLOW, tmp, MEMBERS_COUNT, tradeflow.tftc, tradeflow.tfdesc, tradeflow.tffc)) {
		printf("查询交易流程：%s失败！\n", tmp);
		return -1;
	} else {
		printf("查询交易流程：%s成功。\n", tmp);
		printf("交易代码：%s\n", tradeflow.tftc);
		printf("交易流程说明：%s\n", tradeflow.tfdesc);
		printf("交易流程代码：%s\n", tradeflow.tffc);
		return 0;
	}
}

int do_add_tradeflow(int param)
{
	int c;
	TRADEFLOW tradeflow;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行添加交易流程信息功能...");
	memset(&tradeflow, 0, sizeof(tradeflow));
INPUT_TFTC:
	printf("请输入[添加]交易代码：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TFTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TFTC_SIZE);
		goto INPUT_TFTC;
	}
	memcpy(tradeflow.tftc, tmp, strlen(tmp));
INPUT_TFDESC:
	printf("请输入交易流程说明：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > TFDESC_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", TFDESC_MAXSIZE);
		goto INPUT_TFDESC;
	}
	memcpy(tradeflow.tfdesc, tmp, strlen(tmp));
INPUT_TFFC:
	printf("请输入交易流程代码：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > TFFC_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", TFFC_MAXSIZE);
		goto INPUT_TFFC;
	}
	memcpy(tradeflow.tffc, tmp, strlen(tmp));
	if (sel_db(IT_TRADEFLOW, tradeflow.tftc, 0)) {
		printf("添加交易流程：%s失败，交易流程已经存在！\n", tradeflow.tftc);
		return -1;
	}
	if (!add_db(IT_TRADEFLOW, MEMBERS_COUNT, tradeflow.tftc, tradeflow.tfdesc, tradeflow.tffc)) {
		printf("添加交易流程：%s失败！\n", tradeflow.tftc);
		return -1;
	} else {
		printf("添加交易流程：%s成功。\n", tradeflow.tftc);
		return 0;
	}
}

int do_update_tradeflow(int param)
{
	int c;
	TRADEFLOW tradeflow;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行修改交易流程信息功能...");
	memset(&tradeflow, 0, sizeof(tradeflow));
INPUT_TFTC:
	printf("请输入[修改]交易代码：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TFTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TFTC_SIZE);
		goto INPUT_TFTC;
	}
	memcpy(tradeflow.tftc, tmp, strlen(tmp));
INPUT_TFDESC:
	printf("请输入交易流程说明：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > TFDESC_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", TFDESC_MAXSIZE);
		goto INPUT_TFDESC;
	}
	memcpy(tradeflow.tfdesc, tmp, strlen(tmp));
INPUT_TFFC:
	printf("请输入交易流程代码：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) > TFFC_MAXSIZE) {
		printf("输入数据不能超过%d个字节！\n", TFFC_MAXSIZE);
		goto INPUT_TFFC;
	}
	memcpy(tradeflow.tffc, tmp, strlen(tmp));
	if (!update_db(IT_TRADEFLOW, tradeflow.tftc, MEMBERS_COUNT, tradeflow.tftc, tradeflow.tfdesc, tradeflow.tffc)) {
		printf("修改交易流程：%s失败！\n", tradeflow.tftc);
		return -1;
	} else {
		printf("修改交易流程：%s成功。\n", tradeflow.tftc);
		return 0;
	}
}

int do_del_tradeflow(int param)
{
	int c;
	TRADEFLOW tradeflow;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "执行删除交易流程信息功能...");
	memset(&tradeflow, 0, sizeof(tradeflow));
INPUT_TFTC:
	printf("请输入[删除]的交易代码：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	if (strlen(tmp) != TFTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("输入数据必须是%d个数字！\n", TFTC_SIZE);
		goto INPUT_TFTC;
	}
	if (!del_db(IT_TRADEFLOW, tmp)) {
		printf("删除交易流程：%s失败！\n", tmp);
		return -1;
	} else {
		printf("删除交易流程：%s成功。\n", tmp);
		return 0;
	}
}


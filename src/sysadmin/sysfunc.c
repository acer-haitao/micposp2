#include "all.h"
#include <time.h>
#include <sys/time.h>
#include "tradekey.h"
#include "sysfunc.h"

#define DB_BACKUP_NAME "micposp_db"

bool sys_recover(const char *path);
bool sys_backup(const char *path);

bool sys_init()
{
	LOG(LOG_DEBUG, "系统初始化...");
	if (!check_key()) {
		printf("系统初始化失败，系统异常退出！\n");
		LOG(LOG_ERROR, "系统初始化失败，系统异常退出！");
		return false;
	}
	LOG(LOG_DEBUG, "系统初始化完成。");
	return true;
}

int do_sys_recover(int param)
{
	int c;
	char tmp[FPATH_MAXSIZE + 1], *p;

	LOG(LOG_DEBUG, "执行系统恢复功能...");
	memset(tmp, 0, sizeof(tmp));
	printf("请输入系统备份文件的路径：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	p = trim(tmp);
	LOG(LOG_DEBUG, "系统备份文件的路径：%s。", tmp);
	if (!sys_recover(p)) {
		printf("系统恢复失败，返回菜单！\n");
		return -1;
	} else {
		printf("系统恢复成功，返回菜单。\n");
		return 0;
	}
}

int do_sys_backup(int param)
{
	int c;
	char tmp[FPATH_MAXSIZE + 1], *p;

	LOG(LOG_DEBUG, "执行系统备份功能...");
	memset(tmp, 0, sizeof(tmp));
	printf("请输入系统备份文件的路径（输入0返回菜单）：");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//清空缓存
	p = trim(tmp);
	LOG(LOG_DEBUG, "系统备份文件的路径：%s。", tmp);
	if (!sys_backup(p)) {
		printf("系统备份失败，返回菜单！\n");
		return -1;
	} else {
		printf("系统备份成功，返回菜单。\n");
		return 0;
	}
}

bool sys_recover(const char *path)
{
	int iRet;
	
	LOG(LOG_DEBUG, "系统恢复...");
	if ((iRet = copy_dir(path, DB_PATH)) == -1) {
		LOG(LOG_ERROR, "系统恢复失败！ret: %d path: %s err: %s", iRet, path, strerror(errno));
		return false;
	}
	LOG(LOG_DEBUG, "系统恢复成功，复制%d字节数据。", iRet);
	return true;
}

bool sys_backup(const char *path)
{
	int iRet;
	char tmp[FPATH_MAXSIZE + FNAME_MAXSIZE + 1];
	char ts[20];
	
	LOG(LOG_DEBUG, "系统备份...");
	memset(ts, 0, sizeof(ts));
	sftime(ts, sizeof(ts), "yyyymmddhhmiss");
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "%s/%s_%s", path, DB_BACKUP_NAME, ts);
	if ((iRet = copy_dir(DB_PATH, tmp)) == -1) {
		LOG(LOG_ERROR, "系统备份失败！ret: %d path: err: %s", iRet, tmp, strerror(errno));
		return false;
	}
	LOG(LOG_DEBUG, "系统备份成功，复制%d字节数据。", iRet);
	return true;
}


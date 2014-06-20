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
	LOG(LOG_DEBUG, "ϵͳ��ʼ��...");
	if (!check_key()) {
		printf("ϵͳ��ʼ��ʧ�ܣ�ϵͳ�쳣�˳���\n");
		LOG(LOG_ERROR, "ϵͳ��ʼ��ʧ�ܣ�ϵͳ�쳣�˳���");
		return false;
	}
	LOG(LOG_DEBUG, "ϵͳ��ʼ����ɡ�");
	return true;
}

int do_sys_recover(int param)
{
	int c;
	char tmp[FPATH_MAXSIZE + 1], *p;

	LOG(LOG_DEBUG, "ִ��ϵͳ�ָ�����...");
	memset(tmp, 0, sizeof(tmp));
	printf("������ϵͳ�����ļ���·����");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	p = trim(tmp);
	LOG(LOG_DEBUG, "ϵͳ�����ļ���·����%s��", tmp);
	if (!sys_recover(p)) {
		printf("ϵͳ�ָ�ʧ�ܣ����ز˵���\n");
		return -1;
	} else {
		printf("ϵͳ�ָ��ɹ������ز˵���\n");
		return 0;
	}
}

int do_sys_backup(int param)
{
	int c;
	char tmp[FPATH_MAXSIZE + 1], *p;

	LOG(LOG_DEBUG, "ִ��ϵͳ���ݹ���...");
	memset(tmp, 0, sizeof(tmp));
	printf("������ϵͳ�����ļ���·��������0���ز˵�����");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	p = trim(tmp);
	LOG(LOG_DEBUG, "ϵͳ�����ļ���·����%s��", tmp);
	if (!sys_backup(p)) {
		printf("ϵͳ����ʧ�ܣ����ز˵���\n");
		return -1;
	} else {
		printf("ϵͳ���ݳɹ������ز˵���\n");
		return 0;
	}
}

bool sys_recover(const char *path)
{
	int iRet;
	
	LOG(LOG_DEBUG, "ϵͳ�ָ�...");
	if ((iRet = copy_dir(path, DB_PATH)) == -1) {
		LOG(LOG_ERROR, "ϵͳ�ָ�ʧ�ܣ�ret: %d path: %s err: %s", iRet, path, strerror(errno));
		return false;
	}
	LOG(LOG_DEBUG, "ϵͳ�ָ��ɹ�������%d�ֽ����ݡ�", iRet);
	return true;
}

bool sys_backup(const char *path)
{
	int iRet;
	char tmp[FPATH_MAXSIZE + FNAME_MAXSIZE + 1];
	char ts[20];
	
	LOG(LOG_DEBUG, "ϵͳ����...");
	memset(ts, 0, sizeof(ts));
	sftime(ts, sizeof(ts), "yyyymmddhhmiss");
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "%s/%s_%s", path, DB_BACKUP_NAME, ts);
	if ((iRet = copy_dir(DB_PATH, tmp)) == -1) {
		LOG(LOG_ERROR, "ϵͳ����ʧ�ܣ�ret: %d path: err: %s", iRet, tmp, strerror(errno));
		return false;
	}
	LOG(LOG_DEBUG, "ϵͳ���ݳɹ�������%d�ֽ����ݡ�", iRet);
	return true;
}


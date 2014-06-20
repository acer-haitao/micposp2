#include "all.h"
#include "console.h"
#include "merchants.h"
#include "trademenu.h"
#include "tradeflow.h"
#include "infofunc.h"

#define INFO_DELIM ":"
#define INFO_LINE_MAXSIZE 1024

const char *info_files[] = {
	"merchants.db",
	"trademenu.db",
	"tradeflow.db"
};

typedef struct _info_func_s INFO_FUNC;
struct _info_func_s {
	fun_do_proc do_sel_info;
	fun_do_proc do_add_info;
	fun_do_proc do_update_info;
	fun_do_proc do_del_info;
};

const INFO_FUNC info_funcs[] = {
	{do_sel_merchants, do_add_merchants, do_update_merchants, do_del_merchants},
	{do_sel_trademenu, do_add_trademenu, do_update_trademenu, do_del_trademenu},
	{do_sel_tradeflow, do_add_tradeflow, do_update_tradeflow, do_del_tradeflow}
};

int do_op_info(int param)
{
	switch (HIWORD(param)) {
	case IO_SEL:
		return (info_funcs[LOWORD(param)].do_sel_info)(param);
	case IO_ADD:
		return (info_funcs[LOWORD(param)].do_add_info)(param);
	case IO_UPDATE:
		return (info_funcs[LOWORD(param)].do_update_info)(param);
	case IO_DEL:
		return (info_funcs[LOWORD(param)].do_del_info)(param);
	default:
		return -1;
	}
}

bool sel_db(INFO_TYPE type, char *pid, int count, ...)
{
	FILE *fp;
	char path[FPATH_MAXSIZE + 1], str[INFO_LINE_MAXSIZE + 1];
	char *tmp, *p;
	int i;
	va_list ap;

	sprintf(path, "%s/%s", DB_PATH, info_files[type]);
	if ((fp = fopen(path, "r")) == NULL) {
		LOG(LOG_ERROR, "%s数据库打开失败！err: %s", info_files[type], strerror(errno));
		return false;
	}
	memset(str, 0, sizeof(str));
	while (fgets(str, INFO_LINE_MAXSIZE + 1, fp)) {
		if (memcmp(str, pid, strlen(pid)) == 0) {
			//找到记录
			p = str;
			va_start(ap, count);
			for (i = 0; i < count; i++) {
				tmp = va_arg(ap, char*);
				if (i == 0) {
					p = strtok(str, INFO_DELIM);
				} else {
					p = strtok(NULL, INFO_DELIM);
				}
				if (!p) {
					fclose(fp);
					return false;
				}
				strcpy(tmp, p);
			}
			va_end(ap);
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;
}

bool add_db(INFO_TYPE type, int count, ...)
{
	FILE *fp;
	char path[FPATH_MAXSIZE + 1], str[INFO_LINE_MAXSIZE + 1];
	char *tmp;
	va_list ap;

	sprintf(path, "%s/%s", DB_PATH, info_files[type]);
	if ((fp = fopen(path, "a+")) == NULL) {
		LOG(LOG_ERROR, "%s数据库打开失败！err: %s", info_files[type], strerror(errno));
		return false;
	}
	memset(str, 0, sizeof(str));
	va_start(ap, count);
	while (count--) {
		tmp = va_arg(ap, char*);
		if (strlen(str) + strlen(tmp) + 1 > INFO_LINE_MAXSIZE) {
			LOG(LOG_ERROR, "缓存空间不够，存储失败！");
			return false;
		}
		strcat(str, tmp);
		if (count > 0) {
			strcat(str, INFO_DELIM);
		} else {
			strcat(str, "\n");
		}
	}
	va_end(ap);
	if (fputs(str, fp) == EOF) {
		LOG(LOG_ERROR, "%s数据存储失败！err: %s", info_files[type], strerror(errno));
		return false;
	}
	LOG(LOG_DEBUG, "%s数据存储成功。info: %s", info_files[type], str);
	fflush(fp);
	fclose(fp);
	return true;
}

bool update_db(INFO_TYPE type, char *pid, int count, ...)
{
	int flag;
	FILE *fp, *tmp_fp;
	char path[FPATH_MAXSIZE + 1], tmp_path[FPATH_MAXSIZE + 1], str[INFO_LINE_MAXSIZE + 1];
	char *tmp;
	va_list ap;

	sprintf(path, "%s/%s", DB_PATH, info_files[type]);
	sprintf(tmp_path, "%s.~", path);
	if ((fp = fopen(path, "a+")) == NULL) {
		LOG(LOG_ERROR, "%s数据库打开失败！err: %s", info_files[type], strerror(errno));
		return false;
	}
	if ((tmp_fp = fopen(tmp_path, "w+")) == NULL) {
		LOG(LOG_ERROR, "%s数据库打开失败！err: %s", info_files[type], strerror(errno));
		fclose(fp);
		return false;
	}
	memset(str, 0, sizeof(str));
	flag = 0;
	while (fgets(str, INFO_LINE_MAXSIZE + 1, fp)) {
		if (memcmp(str, pid, strlen(pid)) == 0) {
			//找到记录
			memset(str, 0, sizeof(str));
			va_start(ap, count);
			while (count--) {
				tmp = va_arg(ap, char*);
				if (strlen(str) + strlen(tmp) + 1 > INFO_LINE_MAXSIZE) {
					LOG(LOG_ERROR, "缓存空间不够，存储失败！");
					goto END;
				}
				strcat(str, tmp);
				if (count > 0) {
					strcat(str, INFO_DELIM);
				} else {
					strcat(str, "\n");
				}
			}
			va_end(ap);
			flag = 1;
		}
		fputs(str, tmp_fp);
	}
END:
	fclose(tmp_fp);
	fclose(fp);
	if (!flag) {
		LOG(LOG_ERROR, "找不到记录，%s数据修改失败！pid: %s", info_files[type], pid);
		unlink(tmp_path);
		return false;
	} else {
		if (copy_file(tmp_path, path) == -1) {
			LOG(LOG_ERROR, "%s数据修改失败！pid: %s, err: %s", info_files[type], pid, strerror(errno));
			return false;
		}
		LOG(LOG_DEBUG, "找到记录，%s数据修改成功。pid: %s", info_files[type], pid);
		unlink(tmp_path);
		return true;
	}
}

bool del_db(INFO_TYPE type, char *pid)
{
	int flag;
	FILE *fp, *tmp_fp;
	char path[FPATH_MAXSIZE + 1], tmp_path[FPATH_MAXSIZE + 1], str[INFO_LINE_MAXSIZE + 1];

	sprintf(path, "%s/%s", DB_PATH, info_files[type]);
	sprintf(tmp_path, "%s.~", path);
	if ((fp = fopen(path, "a+")) == NULL) {
		LOG(LOG_ERROR, "%s数据库打开失败！err: %s", info_files[type], strerror(errno));
		return false;
	}
	if ((tmp_fp = fopen(tmp_path, "w+")) == NULL) {
		LOG(LOG_ERROR, "%s数据库打开失败！err: %s", info_files[type], strerror(errno));
		fclose(fp);
		return false;
	}
	memset(str, 0, sizeof(str));
	flag = 0;
	while (fgets(str, INFO_LINE_MAXSIZE + 1, fp)) {
		if (memcmp(str, pid, strlen(pid)) == 0) {
			//找到记录
			flag = 1;
		} else {
			fputs(str, tmp_fp);
		}
	}
	fclose(tmp_fp);
	fclose(fp);
	//整理删除后的数据
	if (!flag) {
		LOG(LOG_ERROR, "找不到记录，%s数据删除失败！pid: %s", info_files[type], pid);
		unlink(tmp_path);
		return false;
	} else {
		if (copy_file(tmp_path, path) == -1) {
			LOG(LOG_ERROR, "%s数据删除失败！pid: %s, err: %s", info_files[type], pid, strerror(errno));
			return false;
		}
		LOG(LOG_DEBUG, "找到记录，%s数据删除成功。pid: %s", info_files[type], pid);
		unlink(tmp_path);
		return true;
	}
}


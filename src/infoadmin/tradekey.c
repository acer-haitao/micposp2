#include "all.h"
#include "infofunc.h"
#include "tradekey.h"

#define KEY_FILE_PATH (DB_PATH"/tradekey.db")

#define KEK_KEY "\x12\x34\x56\x78\x87\x65\x43\x21"
#define DEF_KEY "\x11\x22\x33\x44\x55\x66\x77\x88"
#define VERIFY_VALUE "\x00\x00\x00\x00\x00\x00\x00\x00"

#define KEY_VALUE_LEN 16
#define KEY_DATA_LEN (KEY_VALUE_LEN * 2)

bool set_key_db(byte *value, int size);
bool set_key(const byte key[8]);
bool get_key(byte key[8]);
bool verify_key(byte *value, int size);
bool verify_update_key(byte *value, int size);
bool update_key(char *data, int size);

int do_update_key(int param)
{
	int c;
	char tmp[KEY_DATA_LEN + 1];

	LOG(LOG_DEBUG, "执行更新密钥功能...");
	while (1) {
		memset(tmp, 0, sizeof(tmp));
		printf("请输入新的密钥：");
		scanf("%s", tmp);
		while((c = getchar()) != '\n' && c != EOF);//清空缓存
		if (strlen(tmp) != KEY_DATA_LEN || !isxdigits(tmp, KEY_DATA_LEN)) {
			printf("输入的密钥必须是%d个数字或字母！\n", KEY_DATA_LEN);
			continue;
		}
		if (!update_key(tmp, strlen(tmp))) {
			printf("更新密钥失败，返回菜单！\n");
			return -1;
		} else {
			printf("更新密钥成功，返回菜单。\n");
			return 0;
		}
	}
}

bool update_key(char *data, int size)
{
	byte value[KEY_VALUE_LEN];

	LOG(LOG_DEBUG, "更新密钥...");
	if (!data || size != KEY_DATA_LEN) {
		LOG(LOG_ERROR, "输入参数异常！");
		return false;
	}
	asc2bcd((const char *)data, KEY_DATA_LEN, value, KEY_VALUE_LEN);
	if (!verify_update_key(value, KEY_VALUE_LEN)) {
		LOG(LOG_ERROR, "校验更新密钥失败！");
		return false;
	}
	if (!set_key(value)) {
		LOG(LOG_ERROR, "设置更新密钥失败！");
		return false;
	}
	LOG(LOG_DEBUG, "更新密钥成功。");
	return true;
}

bool verify_update_key(byte *value, int size)
{
	byte okey[8];
	byte tmp[8];

	LOG(LOG_DEBUG, "校验更新密钥...");
	if (!value || size != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "输入参数异常！");
		return false;
	}
	if (!get_key(okey)) {
		LOG(LOG_ERROR, "读取原密钥失败！");
		return false;
	}
	if (_des((const byte*)KEK_KEY, value, KEY_VALUE_LEN) != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "解密更新密钥密文数据错误！");
		return false;
	}
	memcpy(tmp, VERIFY_VALUE, 8);
	if (des(okey, tmp, 8) != 8 || memcmp(value + 8, tmp, 8) != 0) {
		LOG(LOG_ERROR, "更新密钥校验失败！value: %s, mac: %s", hexdumpx(value, KEY_VALUE_LEN, HDX_JOIN, 1), hexdumpx(tmp, 8, HDX_JOIN, 0));
		return false;
	}
	LOG(LOG_DEBUG, "更新密钥校验成功。");
	return true;
}

bool get_key(byte key[8])
{
	int fd, size;
	char data[KEY_DATA_LEN + 1];
	byte value[KEY_VALUE_LEN];

	LOG(LOG_DEBUG, "读取密钥数据...");
	if ((fd = open(KEY_FILE_PATH, O_RDONLY)) == -1) {
		LOG(LOG_ERROR, "密钥数据打开异常！err: %s", strerror(errno));
		return false;
	}
	memset(data, 0, sizeof(data));
	size = read(fd, data, KEY_DATA_LEN);
	close(fd);
	LOG(LOG_DEBUG, "读取密钥数据：%s。", data);
	if (size != KEY_DATA_LEN) {
		LOG(LOG_ERROR, "读取密钥数据长度异常！size: %d", size);
		return false;
	}
	asc2bcd((const char *)data, KEY_DATA_LEN, value, KEY_VALUE_LEN);
	if (!verify_key(value, KEY_VALUE_LEN)) {
		return false;
	}
	memcpy(key, value, 8);
	return true;
}

bool check_key()
{
	int fd, size;
	char data[KEY_DATA_LEN + 1];
	byte value[KEY_VALUE_LEN];

	LOG(LOG_DEBUG, "检查密钥...");
	if ((fd = open(KEY_FILE_PATH, O_RDONLY)) != -1) {
		memset(data, 0, sizeof(data));
		size = read(fd, data, KEY_DATA_LEN);
		close(fd);
		LOG(LOG_DEBUG, "读取密钥数据：%s。", data);
		if (size == KEY_DATA_LEN) {
			asc2bcd((const char *)data, KEY_DATA_LEN, value, KEY_VALUE_LEN);
			if (verify_key(value, KEY_VALUE_LEN)) {
				return true;
			}
		}
	} else {
		LOG(LOG_DEBUG, "密钥文件不存在！err: %s", strerror(errno));
	}
	//恢复为默认密钥并提示用户
	if (!set_defkey()) {
		return false;
	}
	return true;
}

bool verify_key(byte *value, int size)
{
	byte tmp[8];

	LOG(LOG_DEBUG, "校验密钥...");
	if (!value || size != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "输入参数异常！");
		return false;
	}
	if (_des((const byte *)KEK_KEY, value, KEY_VALUE_LEN) != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "解密密钥密文数据错误！");
		return false;
	}
	memcpy(tmp, VERIFY_VALUE, 8);
	if (des(value, tmp, 8) != 8 || memcmp(value + 8, tmp, 8) != 0) {
		LOG(LOG_ERROR, "密钥校验失败！value: %s, mac: %s", hexdumpx(value, KEY_VALUE_LEN, HDX_JOIN, 1), hexdumpx(tmp, 8, HDX_JOIN, 0));
		return false;
	}
	LOG(LOG_DEBUG, "密钥校验正确。");
	return true;
}

bool set_defkey()
{
	LOG(LOG_DEBUG, "设置默认密钥...");
	if (!set_key((const byte *)DEF_KEY)) {
		LOG(LOG_ERROR, "设置默认密钥错误！");
		return false;
	}
	printf("恢复密钥为默认值。");
	LOG(LOG_DEBUG, "恢复密钥为默认值。");
	return true;
}

bool set_key_db(byte *value, int size)
{
	int fd;
	char data[KEY_DATA_LEN + 1];

	LOG(LOG_DEBUG, "设置密钥到密钥数据...");
	if (!value || size != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "输入参数异常！");
		return false;
	}
	if ((fd = open(KEY_FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1) {
		LOG(LOG_ERROR, "密钥数据打开异常！err: %s", strerror(errno));
		return false;
	}
	memset(data, 0, sizeof(data));
	bcd2asc((const byte *)value, size, data, KEY_DATA_LEN);
	if (write(fd, data, KEY_DATA_LEN) == -1) {
		LOG(LOG_ERROR, "更新密钥数据异常！err: %s", strerror(errno));
		return false;
	}
	close(fd);
	LOG(LOG_DEBUG, "设置密钥成功。");
	return true;
}

bool set_key(const byte key[8])
{
	byte value[KEY_VALUE_LEN];
	byte tmp[8];

	LOG(LOG_DEBUG, "设置密钥...");
	memcpy(tmp, VERIFY_VALUE, 8);
	if (des(key, tmp, 8) != 8) {
		LOG(LOG_ERROR, "计算校验值错误！");
		return false;
	}
	memcpy(value, key, 8);
	memcpy(value + 8, tmp, 8);
	if (des((const byte *)KEK_KEY, value, KEY_VALUE_LEN) != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "用户保护密钥加密密钥错误！");
		return false;
	}
	LOG(LOG_DEBUG, "计算密钥密文完成。");
	if (!set_key_db(value, KEY_VALUE_LEN)) {
		return false;
	}
	return true;
}


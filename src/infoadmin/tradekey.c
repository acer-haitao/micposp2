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

	LOG(LOG_DEBUG, "ִ�и�����Կ����...");
	while (1) {
		memset(tmp, 0, sizeof(tmp));
		printf("�������µ���Կ��");
		scanf("%s", tmp);
		while((c = getchar()) != '\n' && c != EOF);//��ջ���
		if (strlen(tmp) != KEY_DATA_LEN || !isxdigits(tmp, KEY_DATA_LEN)) {
			printf("�������Կ������%d�����ֻ���ĸ��\n", KEY_DATA_LEN);
			continue;
		}
		if (!update_key(tmp, strlen(tmp))) {
			printf("������Կʧ�ܣ����ز˵���\n");
			return -1;
		} else {
			printf("������Կ�ɹ������ز˵���\n");
			return 0;
		}
	}
}

bool update_key(char *data, int size)
{
	byte value[KEY_VALUE_LEN];

	LOG(LOG_DEBUG, "������Կ...");
	if (!data || size != KEY_DATA_LEN) {
		LOG(LOG_ERROR, "��������쳣��");
		return false;
	}
	asc2bcd((const char *)data, KEY_DATA_LEN, value, KEY_VALUE_LEN);
	if (!verify_update_key(value, KEY_VALUE_LEN)) {
		LOG(LOG_ERROR, "У�������Կʧ�ܣ�");
		return false;
	}
	if (!set_key(value)) {
		LOG(LOG_ERROR, "���ø�����Կʧ�ܣ�");
		return false;
	}
	LOG(LOG_DEBUG, "������Կ�ɹ���");
	return true;
}

bool verify_update_key(byte *value, int size)
{
	byte okey[8];
	byte tmp[8];

	LOG(LOG_DEBUG, "У�������Կ...");
	if (!value || size != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "��������쳣��");
		return false;
	}
	if (!get_key(okey)) {
		LOG(LOG_ERROR, "��ȡԭ��Կʧ�ܣ�");
		return false;
	}
	if (_des((const byte*)KEK_KEY, value, KEY_VALUE_LEN) != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "���ܸ�����Կ�������ݴ���");
		return false;
	}
	memcpy(tmp, VERIFY_VALUE, 8);
	if (des(okey, tmp, 8) != 8 || memcmp(value + 8, tmp, 8) != 0) {
		LOG(LOG_ERROR, "������ԿУ��ʧ�ܣ�value: %s, mac: %s", hexdumpx(value, KEY_VALUE_LEN, HDX_JOIN, 1), hexdumpx(tmp, 8, HDX_JOIN, 0));
		return false;
	}
	LOG(LOG_DEBUG, "������ԿУ��ɹ���");
	return true;
}

bool get_key(byte key[8])
{
	int fd, size;
	char data[KEY_DATA_LEN + 1];
	byte value[KEY_VALUE_LEN];

	LOG(LOG_DEBUG, "��ȡ��Կ����...");
	if ((fd = open(KEY_FILE_PATH, O_RDONLY)) == -1) {
		LOG(LOG_ERROR, "��Կ���ݴ��쳣��err: %s", strerror(errno));
		return false;
	}
	memset(data, 0, sizeof(data));
	size = read(fd, data, KEY_DATA_LEN);
	close(fd);
	LOG(LOG_DEBUG, "��ȡ��Կ���ݣ�%s��", data);
	if (size != KEY_DATA_LEN) {
		LOG(LOG_ERROR, "��ȡ��Կ���ݳ����쳣��size: %d", size);
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

	LOG(LOG_DEBUG, "�����Կ...");
	if ((fd = open(KEY_FILE_PATH, O_RDONLY)) != -1) {
		memset(data, 0, sizeof(data));
		size = read(fd, data, KEY_DATA_LEN);
		close(fd);
		LOG(LOG_DEBUG, "��ȡ��Կ���ݣ�%s��", data);
		if (size == KEY_DATA_LEN) {
			asc2bcd((const char *)data, KEY_DATA_LEN, value, KEY_VALUE_LEN);
			if (verify_key(value, KEY_VALUE_LEN)) {
				return true;
			}
		}
	} else {
		LOG(LOG_DEBUG, "��Կ�ļ������ڣ�err: %s", strerror(errno));
	}
	//�ָ�ΪĬ����Կ����ʾ�û�
	if (!set_defkey()) {
		return false;
	}
	return true;
}

bool verify_key(byte *value, int size)
{
	byte tmp[8];

	LOG(LOG_DEBUG, "У����Կ...");
	if (!value || size != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "��������쳣��");
		return false;
	}
	if (_des((const byte *)KEK_KEY, value, KEY_VALUE_LEN) != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "������Կ�������ݴ���");
		return false;
	}
	memcpy(tmp, VERIFY_VALUE, 8);
	if (des(value, tmp, 8) != 8 || memcmp(value + 8, tmp, 8) != 0) {
		LOG(LOG_ERROR, "��ԿУ��ʧ�ܣ�value: %s, mac: %s", hexdumpx(value, KEY_VALUE_LEN, HDX_JOIN, 1), hexdumpx(tmp, 8, HDX_JOIN, 0));
		return false;
	}
	LOG(LOG_DEBUG, "��ԿУ����ȷ��");
	return true;
}

bool set_defkey()
{
	LOG(LOG_DEBUG, "����Ĭ����Կ...");
	if (!set_key((const byte *)DEF_KEY)) {
		LOG(LOG_ERROR, "����Ĭ����Կ����");
		return false;
	}
	printf("�ָ���ԿΪĬ��ֵ��");
	LOG(LOG_DEBUG, "�ָ���ԿΪĬ��ֵ��");
	return true;
}

bool set_key_db(byte *value, int size)
{
	int fd;
	char data[KEY_DATA_LEN + 1];

	LOG(LOG_DEBUG, "������Կ����Կ����...");
	if (!value || size != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "��������쳣��");
		return false;
	}
	if ((fd = open(KEY_FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1) {
		LOG(LOG_ERROR, "��Կ���ݴ��쳣��err: %s", strerror(errno));
		return false;
	}
	memset(data, 0, sizeof(data));
	bcd2asc((const byte *)value, size, data, KEY_DATA_LEN);
	if (write(fd, data, KEY_DATA_LEN) == -1) {
		LOG(LOG_ERROR, "������Կ�����쳣��err: %s", strerror(errno));
		return false;
	}
	close(fd);
	LOG(LOG_DEBUG, "������Կ�ɹ���");
	return true;
}

bool set_key(const byte key[8])
{
	byte value[KEY_VALUE_LEN];
	byte tmp[8];

	LOG(LOG_DEBUG, "������Կ...");
	memcpy(tmp, VERIFY_VALUE, 8);
	if (des(key, tmp, 8) != 8) {
		LOG(LOG_ERROR, "����У��ֵ����");
		return false;
	}
	memcpy(value, key, 8);
	memcpy(value + 8, tmp, 8);
	if (des((const byte *)KEK_KEY, value, KEY_VALUE_LEN) != KEY_VALUE_LEN) {
		LOG(LOG_ERROR, "�û�������Կ������Կ����");
		return false;
	}
	LOG(LOG_DEBUG, "������Կ������ɡ�");
	if (!set_key_db(value, KEY_VALUE_LEN)) {
		return false;
	}
	return true;
}


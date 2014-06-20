#include "all.h"
#include "infofunc.h"
#include "merchants.h"

#define MEMBERS_COUNT 4

int do_sel_merchants(int param)
{
	int c;
	MERCHANTS merchants;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ�в�ѯ�̻���Ϣ����...");
	memset(&merchants, 0, sizeof(merchants));
INPUT_MID:
	printf("������[��ѯ]���̻���ţ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != MID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", MID_SIZE);
		goto INPUT_MID;
	}
	if (!sel_db(IT_MERCHANTS, tmp, MEMBERS_COUNT, merchants.mid, merchants.tid, merchants.mname, merchants.mmenu)) {
		printf("��ѯ�̻���%sʧ�ܣ�\n", tmp);
		return -1;
	} else {
		printf("��ѯ�̻���%s�ɹ���\n", tmp);
		printf("�̻���ţ�%s\n", merchants.mid);
		printf("�ն˱�ţ�%s\n", merchants.tid);
		printf("�̻����ƣ�%s\n", merchants.mname);
		printf("�̻��˵���%s\n", merchants.mmenu);
		return 0;
	}
}

int do_add_merchants(int param)
{
	int c;
	MERCHANTS merchants;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ������̻���Ϣ����...");
	memset(&merchants, 0, sizeof(merchants));
INPUT_MID:
	printf("������[���]�̻���ţ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != MID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", MID_SIZE);
		goto INPUT_MID;
	}
	memcpy(merchants.mid, tmp, strlen(tmp));
INPUT_TID:
	printf("�������ն˱�ţ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TID_SIZE);
		goto INPUT_TID;
	}
	memcpy(merchants.tid, tmp, strlen(tmp));
INPUT_MNAME:
	printf("�������̻����ƣ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > MNAME_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", MNAME_MAXSIZE);
		goto INPUT_MNAME;
	}
	memcpy(merchants.mname, tmp, strlen(tmp));
INPUT_MMENU:
	printf("�������̻��˵���");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > MMENU_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", MMENU_MAXSIZE);
		goto INPUT_MMENU;
	}
	memcpy(merchants.mmenu, tmp, strlen(tmp));
	if (sel_db(IT_MERCHANTS, merchants.mid, 0)) {
		printf("����̻���%sʧ�ܣ��̻��Ѿ����ڣ�\n", merchants.mid);
		return -1;
	}
	if (!add_db(IT_MERCHANTS, MEMBERS_COUNT, merchants.mid, merchants.tid, merchants.mname, merchants.mmenu)) {
		printf("����̻���%sʧ�ܣ�\n", merchants.mid);
		return -1;
	} else {
		printf("����̻���%s�ɹ���\n", merchants.mid);
		return 0;
	}
}

int do_update_merchants(int param)
{
	int c;
	MERCHANTS merchants;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ���޸��̻���Ϣ����...");
	memset(&merchants, 0, sizeof(merchants));
INPUT_MID:
	printf("������[�޸�]�̻���ţ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != MID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", MID_SIZE);
		goto INPUT_MID;
	}
	memcpy(merchants.mid, tmp, strlen(tmp));
INPUT_TID:
	printf("�������ն˱�ţ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TID_SIZE);
		goto INPUT_TID;
	}
	memcpy(merchants.tid, tmp, strlen(tmp));
INPUT_MNAME:
	printf("�������̻����ƣ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > MNAME_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", MNAME_MAXSIZE);
		goto INPUT_MNAME;
	}
	memcpy(merchants.mname, tmp, strlen(tmp));
INPUT_MMENU:
	printf("�������̻��˵���");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > MMENU_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", MMENU_MAXSIZE);
		goto INPUT_MMENU;
	}
	memcpy(merchants.mmenu, tmp, strlen(tmp));
	if (!update_db(IT_MERCHANTS, merchants.mid, MEMBERS_COUNT, merchants.mid, merchants.tid, merchants.mname, merchants.mmenu)) {
		printf("�޸��̻���%sʧ�ܣ�\n", merchants.mid);
		return -1;
	} else {
		printf("�޸��̻���%s�ɹ���\n", merchants.mid);
		return 0;
	}
}

int do_del_merchants(int param)
{
	int c;
	MERCHANTS merchants;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ��ɾ���̻���Ϣ����...");
	memset(&merchants, 0, sizeof(merchants));
INPUT_MID:
	printf("������[ɾ��]���̻���ţ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != MID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", MID_SIZE);
		goto INPUT_MID;
	}
	if (!del_db(IT_MERCHANTS, tmp)) {
		printf("ɾ���̻���%sʧ�ܣ�\n", tmp);
		return -1;
	} else {
		printf("ɾ���̻���%s�ɹ���\n", tmp);
		return 0;
	}
}


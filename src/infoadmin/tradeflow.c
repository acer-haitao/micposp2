#include "all.h"
#include "infofunc.h"
#include "tradeflow.h"

#define MEMBERS_COUNT 3

int do_sel_tradeflow(int param)
{
	int c;
	TRADEFLOW tradeflow;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ�в�ѯ����������Ϣ����...");
	memset(&tradeflow, 0, sizeof(tradeflow));
INPUT_TFTC:
	printf("������[��ѯ]�Ľ��״��룺");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TFTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TFTC_SIZE);
		goto INPUT_TFTC;
	}
	if (!sel_db(IT_TRADEFLOW, tmp, MEMBERS_COUNT, tradeflow.tftc, tradeflow.tfdesc, tradeflow.tffc)) {
		printf("��ѯ�������̣�%sʧ�ܣ�\n", tmp);
		return -1;
	} else {
		printf("��ѯ�������̣�%s�ɹ���\n", tmp);
		printf("���״��룺%s\n", tradeflow.tftc);
		printf("��������˵����%s\n", tradeflow.tfdesc);
		printf("�������̴��룺%s\n", tradeflow.tffc);
		return 0;
	}
}

int do_add_tradeflow(int param)
{
	int c;
	TRADEFLOW tradeflow;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ����ӽ���������Ϣ����...");
	memset(&tradeflow, 0, sizeof(tradeflow));
INPUT_TFTC:
	printf("������[���]���״��룺");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TFTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TFTC_SIZE);
		goto INPUT_TFTC;
	}
	memcpy(tradeflow.tftc, tmp, strlen(tmp));
INPUT_TFDESC:
	printf("�����뽻������˵����");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > TFDESC_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", TFDESC_MAXSIZE);
		goto INPUT_TFDESC;
	}
	memcpy(tradeflow.tfdesc, tmp, strlen(tmp));
INPUT_TFFC:
	printf("�����뽻�����̴��룺");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > TFFC_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", TFFC_MAXSIZE);
		goto INPUT_TFFC;
	}
	memcpy(tradeflow.tffc, tmp, strlen(tmp));
	if (sel_db(IT_TRADEFLOW, tradeflow.tftc, 0)) {
		printf("��ӽ������̣�%sʧ�ܣ����������Ѿ����ڣ�\n", tradeflow.tftc);
		return -1;
	}
	if (!add_db(IT_TRADEFLOW, MEMBERS_COUNT, tradeflow.tftc, tradeflow.tfdesc, tradeflow.tffc)) {
		printf("��ӽ������̣�%sʧ�ܣ�\n", tradeflow.tftc);
		return -1;
	} else {
		printf("��ӽ������̣�%s�ɹ���\n", tradeflow.tftc);
		return 0;
	}
}

int do_update_tradeflow(int param)
{
	int c;
	TRADEFLOW tradeflow;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ���޸Ľ���������Ϣ����...");
	memset(&tradeflow, 0, sizeof(tradeflow));
INPUT_TFTC:
	printf("������[�޸�]���״��룺");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TFTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TFTC_SIZE);
		goto INPUT_TFTC;
	}
	memcpy(tradeflow.tftc, tmp, strlen(tmp));
INPUT_TFDESC:
	printf("�����뽻������˵����");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > TFDESC_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", TFDESC_MAXSIZE);
		goto INPUT_TFDESC;
	}
	memcpy(tradeflow.tfdesc, tmp, strlen(tmp));
INPUT_TFFC:
	printf("�����뽻�����̴��룺");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > TFFC_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", TFFC_MAXSIZE);
		goto INPUT_TFFC;
	}
	memcpy(tradeflow.tffc, tmp, strlen(tmp));
	if (!update_db(IT_TRADEFLOW, tradeflow.tftc, MEMBERS_COUNT, tradeflow.tftc, tradeflow.tfdesc, tradeflow.tffc)) {
		printf("�޸Ľ������̣�%sʧ�ܣ�\n", tradeflow.tftc);
		return -1;
	} else {
		printf("�޸Ľ������̣�%s�ɹ���\n", tradeflow.tftc);
		return 0;
	}
}

int do_del_tradeflow(int param)
{
	int c;
	TRADEFLOW tradeflow;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ��ɾ������������Ϣ����...");
	memset(&tradeflow, 0, sizeof(tradeflow));
INPUT_TFTC:
	printf("������[ɾ��]�Ľ��״��룺");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TFTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TFTC_SIZE);
		goto INPUT_TFTC;
	}
	if (!del_db(IT_TRADEFLOW, tmp)) {
		printf("ɾ���������̣�%sʧ�ܣ�\n", tmp);
		return -1;
	} else {
		printf("ɾ���������̣�%s�ɹ���\n", tmp);
		return 0;
	}
}


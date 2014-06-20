#include "all.h"
#include "infofunc.h"
#include "trademenu.h"

#define MEMBERS_COUNT 5

int do_sel_trademenu(int param)
{
	int c;
	TRADEMENU trademenu;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ�в�ѯ���ײ˵���Ϣ����...");
	memset(&trademenu, 0, sizeof(trademenu));
INPUT_TMID:
	printf("������[��ѯ]�Ľ��ײ˵���ţ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TMID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TMID_SIZE);
		goto INPUT_TMID;
	}
	if (!sel_db(IT_TRADEMENU, tmp, MEMBERS_COUNT, trademenu.tmid, trademenu.tmname, trademenu.tmtype, trademenu.tmdesc, trademenu.tmtc)) {
		printf("��ѯ���ײ˵���%sʧ�ܣ�\n", tmp);
		return -1;
	} else {
		printf("��ѯ���ײ˵���%s�ɹ���\n", tmp);
		printf("���ײ˵���ţ�%s\n", trademenu.tmid);
		printf("���ײ˵����ƣ�%s\n", trademenu.tmname);
		printf("���ײ˵����ͣ�%s\n", trademenu.tmtype);
		printf("���ײ˵�˵����%s\n", trademenu.tmdesc);
		printf("���״��룺%s\n", trademenu.tmtc);
		return 0;
	}
}

int do_add_trademenu(int param)
{
	int c;
	TRADEMENU trademenu;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ����ӽ��ײ˵���Ϣ����...");
	memset(&trademenu, 0, sizeof(trademenu));
INPUT_TMID:
	printf("�����뽻�ײ˵���ţ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TMID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TMID_SIZE);
		goto INPUT_TMID;
	}
	memcpy(trademenu.tmid, tmp, strlen(tmp));
INPUT_TMNAME:
	printf("�����뽻�ײ˵����ƣ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > TMNAME_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", TMNAME_MAXSIZE);
		goto INPUT_TMNAME;
	}
	memcpy(trademenu.tmname, tmp, strlen(tmp));
INPUT_TMTYPE:
	printf("�����뽻�ײ˵����ͣ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TMTYPE_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TMTYPE_SIZE);
		goto INPUT_TMTYPE;
	}
	memcpy(trademenu.tmtype, tmp, strlen(tmp));
INPUT_TMDESC:
	printf("�����뽻�ײ˵�˵����");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > TMDESC_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", TMDESC_MAXSIZE);
		goto INPUT_TMDESC;
	}
	memcpy(trademenu.tmdesc, tmp, strlen(tmp));
INPUT_TMTC:
	printf("�����뽻�״��룺");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TMTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TMTC_SIZE);
		goto INPUT_TMTC;
	}
	memcpy(trademenu.tmtc, tmp, strlen(tmp));
	if (sel_db(IT_TRADEMENU, trademenu.tmid, 0)) {
		printf("��ӽ��ײ˵���%sʧ�ܣ����ײ˵��Ѿ����ڣ�\n", trademenu.tmid);
		return -1;
	}
	if (!add_db(IT_TRADEMENU, MEMBERS_COUNT, trademenu.tmid, trademenu.tmname, trademenu.tmtype, trademenu.tmdesc, trademenu.tmtc)) {
		printf("��ӽ��ײ˵���%sʧ�ܣ�\n", trademenu.tmid);
		return -1;
	} else {
		printf("��ӽ��ײ˵���%s�ɹ���\n", trademenu.tmid);
		return 0;
	}
}

int do_update_trademenu(int param)
{
	int c;
	TRADEMENU trademenu;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ���޸Ľ��ײ˵���Ϣ����...");
	memset(&trademenu, 0, sizeof(trademenu));
INPUT_TMID:
	printf("������[�޸�]���ײ˵���ţ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TMID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TMID_SIZE);
		goto INPUT_TMID;
	}
	memcpy(trademenu.tmid, tmp, strlen(tmp));
INPUT_TMNAME:
	printf("�����뽻�ײ˵����ƣ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > TMNAME_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", TMNAME_MAXSIZE);
		goto INPUT_TMNAME;
	}
	memcpy(trademenu.tmname, tmp, strlen(tmp));
INPUT_TMTYPE:
	printf("�����뽻�ײ˵����ͣ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TMTYPE_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TMTYPE_SIZE);
		goto INPUT_TMTYPE;
	}
	memcpy(trademenu.tmtype, tmp, strlen(tmp));
INPUT_TMDESC:
	printf("�����뽻�ײ˵�˵����");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) > TMDESC_MAXSIZE) {
		printf("�������ݲ��ܳ���%d���ֽڣ�\n", TMDESC_MAXSIZE);
		goto INPUT_TMDESC;
	}
	memcpy(trademenu.tmdesc, tmp, strlen(tmp));
INPUT_TMTC:
	printf("�����뽻�״��룺");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TMTC_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TMTC_SIZE);
		goto INPUT_TMTC;
	}
	memcpy(trademenu.tmtc, tmp, strlen(tmp));
	if (!update_db(IT_TRADEMENU, trademenu.tmid, MEMBERS_COUNT, trademenu.tmid, trademenu.tmname, trademenu.tmtype, trademenu.tmdesc, trademenu.tmtc)) {
		printf("�޸Ľ��ײ˵���%sʧ�ܣ�\n", trademenu.tmid);
		return -1;
	} else {
		printf("�޸Ľ��ײ˵���%s�ɹ���\n", trademenu.tmid);
		return 0;
	}
}

int do_del_trademenu(int param)
{
	int c;
	TRADEMENU trademenu;
	char tmp[INFO_MAXINPUT + 1];

	LOG(LOG_DEBUG, "ִ��ɾ�����ײ˵���Ϣ����...");
	memset(&trademenu, 0, sizeof(trademenu));
INPUT_TMID:
	printf("������[ɾ��]�Ľ��ײ˵���ţ�");
	scanf("%s", tmp);
	while((c = getchar()) != '\n' && c != EOF);//��ջ���
	if (strlen(tmp) != TMID_SIZE || !isdigits(tmp, strlen(tmp))) {
		printf("�������ݱ�����%d�����֣�\n", TMID_SIZE);
		goto INPUT_TMID;
	}
	if (!del_db(IT_TRADEMENU, tmp)) {
		printf("ɾ�����ײ˵���%sʧ�ܣ�\n", tmp);
		return -1;
	} else {
		printf("ɾ�����ײ˵���%s�ɹ���\n", tmp);
		return 0;
	}
}


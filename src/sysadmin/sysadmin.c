#include "all.h"
#include "sysadmin.h"

bool sysinit()
{
	//��齻����Կ�Ƿ���ڣ��������򴴽�Ĭ�ϵ���Կ
	if (!check_key())
		return false;

	return true;
}


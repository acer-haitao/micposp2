#include "all.h"
#include "sysadmin.h"

bool sysinit()
{
	//检查交易密钥是否存在，不存在则创建默认的密钥
	if (!check_key())
		return false;

	return true;
}


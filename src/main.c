#include "all.h"
#include "console.h"
#include "sysfunc.h"

int main(int argc, char *argv[])
{
	LOG(LOG_DEBUG, "\n====================================micposp sys start====================================");
	if (!sys_init()) {
		return -1;
	}
	console();
	LOG(LOG_DEBUG, "\n====================================micposp sys stop=====================================");
	return 0;
}


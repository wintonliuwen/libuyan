#include <lwzy.h>


pid_t getPidByName( char* name )
{
	char command[30] = {0};
	char buf[20] = {0};
	int ret = 0;
	FILE *fp_read = NULL;
	pid_t pid = -1;
	sprintf(command, "pidof %s", name);
	if ((fp_read = popen(command, "r")) != NULL)
	{
		ret = fread(buf, sizeof(char), 20, fp_read);
		pclose(fp_read);
	}
	else
	{
		return -1;
	}

	if (ret > 0)
		pid = atoi(buf);

	return pid;	
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <lwzy.h>


int main(int argc, char **argv)
{
	int fd = open("/dev/abc", O_RDWR);
	if (fd < 0)
		err_sys("openfile error\n");

	if (close(fd) < 0)
		err_sys("close file error\n");

	return 0;	
}

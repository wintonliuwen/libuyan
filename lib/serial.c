#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>


int tc_setspeed(int fd, speed_t speed)
{
	struct termios term;
	if (tcgetattr(fd, &term) < 0)
	{
		err_ret("get %d attributes error", fd);
		return -1;
	}

	tcflush(fd, TCIOFLUSH);

	if (cfsetispeed(&term, speed) < 0)
	{
		err_ret("set input speed error");
	}

	if (cfsetospeed(&term, speed) < 0)
	{
		err_ret("set output speed error");
	}

	if (tcsetattr(fd, TCSANOW, &term) < 0)
	{
		err_ret("set attribute error");
		return -1;
	}

	tcflush(fd, TCIOFLUSH);

	return 0;

}


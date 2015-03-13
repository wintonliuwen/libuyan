#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <cflink.h>

int main(int argc, char **argv)
{
	CF_COMMAND *cf_command = cfcmd_combine(TYPE_TRANS, DEV_IRBLASTER, CMD_SND);
	if (cf_command != NULL)
		dump_cfcmd(*cf_command);
	CF_PACKET *cfpkt = cfpkt_combine(3, *cf_command, "P01:RAW:0000");
	char *buf = cfpacket2protol(*cfpkt);
	printf("buf:%s\n", buf);
}

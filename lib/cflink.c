#include <lwzy.h>
#include <cflink.h>

CF_COMMAND *cfcmd_combine(char type, char *device, char *cmdname)
{
	if (strlen(device) != 3 || strlen(cmdname) != 3)
	{
		err_msg("device or cmdname illegal");
		return NULL;
	}
	
	CF_COMMAND *cf_command = (CF_COMMAND *)malloc(sizeof(CF_COMMAND));

	if (cf_command == NULL)	
	{
		err_msg("allocate cf_command failed");
		return NULL;
	}


	cf_command->cmd_type = type;
	strncpy(cf_command->cmd_device, device, strlen(device));
	strncpy(cf_command->cmd_cmdname, cmdname, strlen(cmdname));
	return cf_command;
}

CF_PACKET *cfpkt_combine(char cf_id, CF_COMMAND cf_command, char *data)
{
	if (!((2 <= cf_id && cf_id <= 0xef) || cf_id == BROADCASK_ID))
	{
		err_msg("illegal cf_id");
		return NULL;
	}

	if (data == NULL)
	{
		err_msg("illegal cf_data");
		return NULL;
	}

	CF_PACKET *cf_packet = (CF_PACKET *)malloc(sizeof(CF_PACKET));
	if (cf_packet == NULL)
	{
		err_msg("malloc cf_packet failed");
		return NULL;
	}

	int datalen = strlen(data);
	
	cf_packet->cf_id = cf_id;
	cf_packet->cf_command = cf_command;
	cf_packet->cf_data = calloc(datalen+1, sizeof(data));
	strncpy(cf_packet->cf_data, data, strlen(data));
	/*data[len] = '\0' the end flag*/
	cf_packet->cf_data[datalen] = '\0';
	
	return cf_packet;
}

char *cfpacket2protol(CF_PACKET cfpacket)
{
	int datalen = strlen(cfpacket.cf_data);
	/*
	  [F2]id[F3]command[F4]data[F5][F5]
	   4  1   4   7     4       4   4
	*/
	int totallen = 29 + datalen;
	char *buf = calloc(totallen, sizeof(char));
	if (buf == NULL)
	{
		err_msg("malloc buf failed");
		return NULL;
	}

	sprintf(buf, "[F2]%d[F3]%7.7s[F4]%s[F5][F5]", cfpacket.cf_id,(char *)&cfpacket.cf_command, cfpacket.cf_data);
	return buf;
}

void dump_cfcmd(CF_COMMAND cf_cmd)
{   
    char cmd_device[4] = {0};
    char cmd_cmdname[4] = {0};
    strncpy(cmd_device, cf_cmd.cmd_device, sizeof(cf_cmd.cmd_device)); 
    strncpy(cmd_cmdname, cf_cmd.cmd_cmdname, sizeof(cf_cmd.cmd_cmdname));
    printf("type:%c\n", cf_cmd.cmd_type);
    printf("device:%s\n",cmd_device);
    printf("cmdname:%s\n",cmd_cmdname);
}

void dump_cfpacket(CF_PACKET cf_packet)
{
	printf("id:0x%02x\n", cf_packet.cf_id);
	dump_cfcmd(cf_packet.cf_command);
	printf("data:%s\n",cf_packet.cf_data);
}

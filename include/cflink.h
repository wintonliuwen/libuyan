#ifndef _CFLINK_H
#define _CFLINK_H


/* CFLINK PROTOCOL
 [F2]<ID>[F3]<COMMAND>[F4]<DATA>[F5][F5]
 COMMAND: <TYPE><DEVICE><COMMAND_NAME>
*/

#define CFIDTAG "<F2>"
#define CFCMDTAG "<F3>"
#define CFDATATAG "<F4>"
#define CFENDTAG "<F5><F5>"


/* ID */
#define BROADCASK_ID 0xff


/* TYPE */
#define TYPE_QUERY 'Q'
#define TYPE_CONFIG 'C'
#define TYPE_TRANS 'T'
#define TYPE_REPLY 'R'

/* DEVICE */
#define DEV_IRBLASTER "IRB"

/* COMMAND */
#define CMD_SND "SND"

typedef struct cflink_command{
	char cmd_type;
	char cmd_device[3];
	char cmd_cmdname[3];
} CF_COMMAND;


typedef struct cflink_packet{
	char cf_id;
	CF_COMMAND cf_command;
	char *cf_data;
} CF_PACKET;


CF_COMMAND *cfcmd_combine(char type, char *device, char *cmdname);
CF_PACKET *cfpkt_combine(char cf_id, CF_COMMAND cf_command, char *data);
char *cfpacket2protol(CF_PACKET cfpacket);
void dump_cfcmd(CF_COMMAND cf_cmd);
void dump_cfpacket(CF_PACKET cf_packet);


#endif

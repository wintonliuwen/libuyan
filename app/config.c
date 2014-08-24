#include <lwzy.h>
#include <config_fun.h>

int main(int argc, char **argv)
{
	struct config *cfg;
	FILE *fp = NULL;
	fp = fopen(argv[1], "r");
	cfg = cfg_load_file(fp);
	fclose(fp);
	printf("host:%s\n", cfg_getstr(cfg, "host"));
	printf("port:%d\n", cfg_getnum(cfg, "port"));
	return 0;
}

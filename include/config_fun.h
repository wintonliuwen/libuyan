/*======================================================================
#
# Author: Winton - newtonliuwen@gmail.com
#
# Last modified: 2014-08-24 22:13
#
# Filename: config_fun.h
#
# Description: 
#
======================================================================*/
#ifndef _CONFIG_FUN_H
#define _CONFIG_FUN_H
#define TRUE    1
#define FALSE   0
typedef unsigned char     BOOL;

struct config{
    int size;
    int count;
    char *key; /* if(key == "#") 就是注释 */
    char *val;
    struct config *parent;
    struct config *next;
    struct config *items;
};


struct config *cfg_load_file(FILE *fp);
struct config *add_node(struct config *parent, char *key, char *val, int lineno);

void cfg_print(struct config *cfg, FILE *fp);

void cfg_free(struct config *cfg);
struct config *cfg_get_next(struct config *cfg);
struct config *cfg_get_first(struct config *cfg);
extern int cfg_del_child(struct config *cfg, char *key, char *val);
extern struct config *cfg_find_child(struct config *cfg, char *key);
struct config *cfg_get(struct config *cfg, char *key);

int cfg_num(struct config *cfg);
char *cfg_str(struct config *cfg);

int cfg_getnum(struct config *cfg, char *key);
char *cfg_getstr(struct config *cfg, char *key);

#endif

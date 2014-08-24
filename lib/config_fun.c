/**
 * @author: ideawu
 * @url: http://www.ideawu.net
 * @description: C 语言使用配置文件库.
 */
#include <lwzy.h>
#include <assert.h>
#include "config_fun.h"
#include "config_string.h"
#define CONFIG_MAX_LINE     1024
#define IS_COMMENT_CONFIG(c)    ((c)->key[0] == '#')

#define PRINT_TRACE(fmt, args...)   printf(__FILE__ "(%d): " fmt "\n", __LINE__, ##args)

int is_kv_seperator(int ch){
    return strchr(":=", ch) != NULL;
}

struct config *cfg_find_child(struct config *cfg, char *key);

struct config *add_node(struct config *parent, char *key, char *val, int lineno){
    struct config *cfg;
    int size;
    int i;
#if 0
    if(key[0] != '#' && cfg_find_child(parent, key)){
        pm_printf(PM_PUBLIC, PM_LOG_ERR,"line: %d, duplicated '%s'", lineno, key);
        return NULL;
    }
#endif
    if(parent->size == parent->count){
        size = parent->size * 2 + 5;
        cfg = (struct config *)realloc(parent->items, size * sizeof(*cfg));
        if(!cfg){
            return NULL;
        }

        parent->items = cfg;
        parent->size = size;

        i = 0;
        while(i < parent->count - 1)
        {
            parent->items[i].next = &parent->items[i + 1];
            i++;
        }
        parent->items[i].next = NULL;
    }
    
    cfg = &parent->items[parent->count++];
    cfg->parent = parent;
    cfg->items = NULL;
    cfg->next  = NULL;
    cfg->size = cfg->count = 0;

    cfg->key = (char *)malloc(strlen(key) + 1);
    assert(cfg->key);
    strcpy(cfg->key, key);

    cfg->val = (char *)malloc(strlen(val) + 1);
    assert(cfg->val);
    strcpy(cfg->val, val);
    if(parent->count > 1)
    {
        parent->items[parent->count - 2].next = cfg;
    }
    return cfg;
}

struct config *cfg_load_file(FILE *fp){
    struct config *root_cfg, *cfg;
    char buf[CONFIG_MAX_LINE + 3];
    char *key, *val;
    int lineno = 0;
    int indent, last_indent;
    int i, len;

    root_cfg = (struct config *)calloc(1, sizeof(*cfg));
    if(!root_cfg){
        goto err;
    }
    root_cfg->key = (char*)malloc(strlen("root") + 1);
    assert(root_cfg->key);
    strcpy(root_cfg->key, "root");

    root_cfg->val = (char*)malloc(strlen("") + 1);
    assert(root_cfg->val);
    strcpy(root_cfg->val, "");

    cfg = root_cfg;
    last_indent = 0;

    while(fgets(buf, sizeof(buf), fp)){
        lineno++;

        rtrim(buf);
        len = strlen(buf);

        if(len > CONFIG_MAX_LINE){
          
            goto err;
        }
        if(is_empty_str(buf)){
            continue;
        }

        indent = 0;
        key = buf;
        while(*key == '\t'){
            indent++;
            key++;
        }

        if(indent <= last_indent){
            for(i = indent; i <= last_indent; i++){
                if(cfg != root_cfg){
                    cfg = cfg->parent;
                }
            }
        }else if(indent > last_indent + 1){
            goto err;
        }

        if(*key == '#'){
            cfg = add_node(cfg, "#", key + 1, lineno);
            if(cfg == NULL){
                goto err;
            }
            last_indent = indent;
            continue;
        }else if(is_whitespace(*key)){
            goto err;
        }

        val = key;
        while(*val && !is_kv_seperator(*val)){
            val++;
        }
        if(*val == '\0'){
            goto err;
        }else if(!is_kv_seperator(*val)){
            goto err;
        }
        *val++ = '\0';

        key = trim(key);
        val = trim(val);

        cfg = add_node(cfg, key, val, lineno);
        if(cfg == NULL){
            goto err;
        }

        last_indent = indent;
    }

    return root_cfg;

err:
    if(root_cfg){
        cfg_free(root_cfg);
    }

    return NULL;
}

void _cfg_free(struct config *cfg, int indent){
    struct config *c;
    int i;

    if(cfg->key){
        free(cfg->key);
    }
    if(cfg->val){
        free(cfg->val);
    }
    if(cfg->items){
        for(i = 0; i < cfg->count; i++){
            c = &cfg->items[i];
            _cfg_free(c, indent + 1);
        }
        free(cfg->items);
    }
}

void cfg_free(struct config *cfg){
    _cfg_free(cfg, 0);
    free(cfg);
}

struct config *cfg_find_child(struct config *cfg, char *key){
    struct config *c;
    int i;

    for(i = 0; i < cfg->count; i++){
        c = &cfg->items[i];
        if(strcmp(key, c->key) == 0){
            return c;
        }
    }

    return NULL;
}

int cfg_del_child(struct config *cfg, char *key, char *val)
{
    struct config *c;
    int i;
    BOOL exsit = FALSE;

    if(cfg->count == 0)
    {
        return 0;
    }

    for(i = 0; i < cfg->count; i++)
    {
        c = &cfg->items[i];
        if(exsit == FALSE &&strcmp(key, c->key) == 0 && strcmp(val, c->val) == 0)
        {
            _cfg_free(c,0);
            exsit = TRUE;
        }

        if(exsit)
        {
            if(i == cfg->count - 1)
            {
                break;
            }
            memcpy(&cfg->items[i],cfg->items[i].next,sizeof(struct config));
        }
    }

    if(exsit)
    {
        cfg->count--;
        for(i = 0; i < cfg->count - 1; i++)
        {
            cfg->items[i].next = &cfg->items[i + 1];
        }
        if(cfg->count)
        {
            cfg->items[cfg->count-1].next = NULL;
        }
        return 0;
    }

    return -1;
}

struct config *cfg_get_next(struct config *cfg)
{
    assert(cfg);
    return cfg->next;
}

struct config *cfg_get_first(struct config *cfg)
{
    assert(cfg);

    if(cfg->count == 0)
    {
        return NULL;
    }

    return &cfg->items[0];
}


struct config *cfg_get(struct config *cfg, char *key){
    char path[CONFIG_MAX_LINE];
    struct config *c;
    char *f, *fs; /* field, field seperator */

    assert(key);
    c = cfg;
    strcpy(path, key);

    f = fs = path;
    while(c){
        switch(*fs++){
            case '.':
            case '/':
                *(fs - 1) = '\0';
                c = cfg_find_child(c, f);
                f = fs;
                break;
            case '\0':
                c = cfg_find_child(c, f);
                return c;
            default:
                break;
        }
    }

    return c;
}

int cfg_num(struct config *cfg){
    return atoi(cfg->val);
}

char *cfg_str(struct config *cfg){
    return cfg->val;
}

int cfg_getnum(struct config *cfg, char *key){
    int val;
    struct config *c;

    c = cfg_get(cfg, key);
    if(!c){
        return 0;
    }

    val = atoi(c->val);
    return val;
}

char *cfg_getstr(struct config *cfg, char *key){
    struct config *c;

    c = cfg_get(cfg, key);
    if(!c){
        return NULL;
    }

    return c->val;
}

void _cfg_print(struct config *cfg, int indent, FILE *fp){
    struct config *c;
    char fs;
    int i, n;

    for(i = 0; i < cfg->count; i++){
        c = &cfg->items[i];
        for(n = 0; n < indent; n++){
            putc('\t', fp);
        }

        if(IS_COMMENT_CONFIG(c)){
            fprintf(fp, "#%s\n", c->val);
        }else{
            fs = c->count? ':' : '=';
            fprintf(fp, "%s %c %s\n", c->key, fs, c->val);
        }

        if(c->count > 0){
            _cfg_print(c, indent + 1, fp);
        }
    }
}

void cfg_print(struct config *cfg, FILE *fp){
    _cfg_print(cfg, 0, fp);
}

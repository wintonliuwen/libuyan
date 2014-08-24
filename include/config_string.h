/*======================================================================
#
# Author: Winton - newtonliuwen@gmail.com
#
# Last modified: 2014-08-24 21:51
#
# Filename: config_string.h
#
# Description: 
#
======================================================================*/
#ifndef UTIL__STRING_H
#define UTIL__STRING_H

#include <string.h>

unsigned long long  g_total_mem = 0;
int is_whitespace(const int ch)
{
    return strchr(" \t\r\n", ch) != NULL;
};

int is_alpha(const int ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
};

int is_digit(const int ch){
    return (ch >= '0' && ch <= '9');
};

int is_wordchar(const int ch){
    return (ch == '_') || is_alpha(ch) || is_digit(ch);
};

int is_empty_str(const char *str){
    const char *p = str;
    while(*p && is_whitespace(*p)){
        p++;
    }
    return *p == '\0';
};

/* 返回左边不包含空白字符的字符串的指针 */
char *ltrim(char *str){
    char *p = str;
    while(*p && is_whitespace(*p)){
        p++;
    }
    return p;
};

/* 返回右边不包含空白字符的字符串的指针 */
char *rtrim(char *str){
    char *p;
    p = str + strlen(str) - 1;
    while(p >= str && is_whitespace(*p)){
        p--;
    }
    *(p + 1) = '\0';
    return str;
};

/* 返回左右两边不包含空白字符的字符串的指针 */
char *trim(char *str){
    char *p;
    p = ltrim(str);
    rtrim(p);
    return p;
};

#endif

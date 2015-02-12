#ifndef _LWZY_H
#define _LWZY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include <stdarg.h>

#define MAXLINE 4096            /* max line length */

pid_t getPidByName( char* name );

/* error */
void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_exit(int error, const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);

#endif

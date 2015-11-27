/*
 * =====================================================================================
 *
 *       Filename:  Log.c
 *
 *    Description:  impl for the log class
 *
 *        Version:  1.0
 *        Created:  22.02.2010 16:21:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kai Beckmann (kai), kai-oliver.beckmann@hs-rm.de
 *        Company:  Hochschule RheinMain - DOPSY Labor für verteilte Systeme
 *
 * =====================================================================================
 */

#include "Log.h"

#include <contiki.h>
#include <contiki-net.h>
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>

#include <stdarg.h>
#include <stdlib.h>

#define PRINTF(FORMAT,args...) printf_P(PSTR(FORMAT),##args)

// 0 all, 1
static int logLvl =0;

void Log_setLvl(int lvl)
{
    logLvl = lvl;
}
#ifndef UTILS_NO_LOGGING
void _log_trace(const char* fnk, ...)
{
    if (logLvl < 1 ) {
        va_list arg;
        char* string;
        va_start(arg, fnk);

        string = va_arg(arg, char*);
        PRINTF("TRACE: %s() : ", fnk);

        vprintf(string, arg);
        va_end(arg);
    }
}

void _log_debug(const char* fnk, ...)
{
    if (logLvl < 2 ) {
        va_list arg;
        char* string;
        va_start(arg, fnk);

        string = va_arg(arg, char*);
        PRINTF("DEBUG: %s() : ", fnk);

        vprintf(string, arg);
        va_end(arg);
    }
}

void _log_info(const char* fnk, ...)
{
    if (logLvl < 3) {
        va_list arg;
        char* string;
        va_start(arg, fnk);

        string = va_arg(arg, char*);

        PRINTF("INFO: %s() : ", fnk);
        vprintf(string, arg);

        va_end(arg);
    }
}

void _log_warn(const char* fnk, ...)
{
    if (logLvl < 4) {
        va_list arg;
        char* string;
        va_start(arg, fnk);

        string = va_arg(arg, char*);
        PRINTF("WARN: %s() : ", fnk);

        vprintf(string, arg);
        va_end(arg);
    }
}

void _log_error(const char* fnk, ...)
{
    if (logLvl < 5){
        va_list arg;
        char* string;
        va_start(arg, fnk);

        string = va_arg(arg, char*);
        PRINTF("ERROR: %s() : ", fnk);

        vprintf(string, arg);
        va_end(arg);
    }
}

void _log_panic(const char* fnk, ...)
{
    if (logLvl < 6) {
        va_list arg;
        char* string;
        va_start(arg, fnk);

        string = va_arg(arg, char*);
        PRINTF("PANIC: %s() : ", fnk);

        vprintf(string, arg);
        va_end(arg);
        abort();
    }
}
#endif



#include "logger.h"
#include <stdarg.h>

static FILE *log_file = NULL;
static int log_calls_count = 0;

void logSetFile(FILE *file)
{
    log_file = file;
}

void logPrintf(const char *format, ...)
{
    if (!log_file)
    {
        return;
    }

    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);

    log_calls_count++;
}

int getLogCallsCount() {
    return log_calls_count;
}

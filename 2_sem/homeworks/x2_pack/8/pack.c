#include "pack.h"
#include <stdarg.h>
#include <string.h>

int pack(char *buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int total = 0;
    char *ptr = buffer;

    for (const char *p = format; *p; p++)
    {
        if (*p != '%') continue;
        p++;
        switch (*p)
        {
            case 'd':
            {
                int val = va_arg(args, int);
                if (ptr)
                {
                    memcpy(ptr, &val, sizeof(int));
                    ptr += sizeof(int);
                }
                total += sizeof(int);
                break;
            }
            case 'l':
            {
                if (*(p + 1) == 'f')
                {
                    p++;
                    double val = va_arg(args, double);
                    if (ptr)
                    {
                        memcpy(ptr, &val, sizeof(double));
                        ptr += sizeof(double);
                    }
                    total += sizeof(double);
                }
                break;
            }
            case 's':
            {
                char *str = va_arg(args, char*);
                size_t len = strlen(str) + 1;
                if (ptr)
                {
                    memcpy(ptr, str, len);
                    ptr += len;
                }
                total += len;
                break;
            }
        }
    }

    va_end(args);
    return total;
}

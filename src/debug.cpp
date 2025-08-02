#include <cstdio>
#include <cstdarg>

#include "debug.h"

void tp::tp_assert(const bool assertion, const char* const expression, const char* const file, const unsigned int line)
{    
    if(!assertion)
    {
        while(true)
        {
            printf("Assertion failed at %s line %d (%s).\n", file, line, expression);
            sleep_ms(2500);
        }
    } 
}

void tp::tp_assert(const bool assertion, const char* const expression, const char* const file, const unsigned int line, const char* const message, ...)
{
    if(!assertion)
    {
        va_list args;
        va_start(args, message);
        while(true)
        {
            printf("Assertion failed at %s line %d (%s): ", file, line, expression);
            vprintf(message, args);
            printf("\n");
            sleep_ms(2500);
        }
    } 

}

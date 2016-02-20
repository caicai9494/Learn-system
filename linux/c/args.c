#include <common.h>

#include <stdarg.h>

void LOG_EVERYTHING(char* fmt, ...);
    // This function demonstrates the use of
    // 'va_list', 'va_arg', 'va_start' and 'va_end'.
    
void LOG_INFO(char* fmt, ...);
    // This function demonstrates the use of
    // 'vprintf'.

int main()
{
    LOG_EVERYTHING("a", "b", "c");
    LOG_INFO("int %d, string %s\n", 5, "hello");
}

void LOG_EVERYTHING(char* fmt, ...)
{
    char* str = fmt;

    va_list vlst;
    va_start(vlst, fmt);

    do {
	puts(str);
	str = va_arg(vlst, char*);
    } while (str != NULL);

    va_end(vlst);
}

void LOG_INFO(char* fmt, ...)
{
    va_list vlst;
    va_start(vlst, fmt);
    vprintf(fmt, vlst);
    va_end(vlst);
}

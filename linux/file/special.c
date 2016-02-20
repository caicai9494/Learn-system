#include <common.h>

int main()
{
    char buf[128];
    int ret = open("/dev/random", buf, 128);
    printf("%s\n", buf);
}

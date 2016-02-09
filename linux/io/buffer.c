#include <common.h>

int main()
{
    char buffer[BUFSIZ + 1];
    int setvbuf(stdout, buffer, _IOFBF, BUFSIZ);  
}

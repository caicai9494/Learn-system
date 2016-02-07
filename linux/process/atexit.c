#include "common.h"

void onExit() 
{
    printf("exiting...\n");
}

int main()
{
    if (0 != atexit(onExit)) {
	perror("atexit");
    }

    // Notice, 'exec' will clear out all registered
    // handlers
    int ret;
    ret = execl("/bin/echo", "echo", "temp", NULL);
    if (-1 == ret) {
	perror("execl");
    }
}

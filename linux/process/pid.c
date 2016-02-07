#include "common.h"

#include <stdio.h>

void traverse_pid(pid_t pid);

int main()
{
    return 0;
}

void traverse_pid(pid_t pid)
{
    if (pid == 1) {
	return;
    }	

    // oops! getppid() is only aware of current 
    // process's parrent and nothing else, which
    // means it's impossible to traverse =/
    pid_t ppid = getppid();

}


#include "common.h"
#include <string.h>

#define PID_MAX 10

int main()
{
    pid_t pids[PID_MAX];
    memset(pids, 0, PID_MAX);

    int i, ret, count = 10000;
    for (i = 0; i != PID_MAX; ++i) {
	ret = fork();

	if (0 == ret) {
	    
	    while (count--)
		; // looping...
	    printf("%d done!\n", getpid());
	}
	else {
	    pids[i] = ret;
	}
    }

    for (i = 0; i != PID_MAX; ++i) {
	int status;
	waitpid(pids[i], &status, WNOHANG|WUNTRACED|WCONTINUED);
    }
}

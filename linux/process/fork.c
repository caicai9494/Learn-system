#include "common.h"

int main()
{
    int ret = 0;

    int shared = 5;

    ret = fork();

    if (0 == ret) {
	// spawned process
	sleep(1);
	shared += 10;
	printf("shared is %d after modify in son\n", shared);
	printf("shared address is %p in son\n", &shared);
    }
    else if(ret > 0) {
	// parent process
	// son's pid is returned
	printf("shared is %d after modify in parrent\n", shared);
	printf("shared address is %p in parent\n", &shared);

	wait(NULL);
	printf("shared address is %p in parent\n", &shared);
    }
    else {
	perror("fork");
    }
}

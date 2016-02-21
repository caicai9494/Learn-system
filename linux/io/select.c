#include <common.h>

int main()
{
    fd_set readfds, writefds;
    int ret, nfds, fd, i, j;
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);

    // won't work since no data in the buffer
    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(STDOUT_FILENO, &readfds);

    FD_SET(STDOUT_FILENO, &writefds);
    FD_SET(STDIN_FILENO, &writefds);

    nfds = STDOUT_FILENO > STDIN_FILENO ? 
	STDOUT_FILENO : STDIN_FILENO;

    ret = select(nfds + 1, &readfds, &writefds, NULL, &timeout);
    if (ret < 0) {
	perror("select");
	exit(1);
    }

    for (i = 0; i < nfds + 1; i++) {
	printf("%d %s%s\n", i, FD_ISSET(i, &readfds) ? "r" : "", FD_ISSET(i, &writefds) ? "w" : "");
    }

    printf("timeout remaining %ld.%03ld\n",
	    timeout.tv_sec, timeout.tv_usec/10000);

}


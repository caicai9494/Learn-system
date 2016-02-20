#include <common.h>
#define MAXLINE 128

char buffer[MAXLINE];

int main()
{
    int n;
    int fd[2];
    pid_t pid;

    if (pipe(fd) < 0) {
	perror("pipe");
	exit(1);
    }

    if ((pid = fork()) < 0) {
	perror("fork");
	exit(1);
    }
    if (pid > 0) { /* parent */
	close(fd[0]);
	//write(fd[1], "hello\n", 6); 
	close(fd[1]);
	//write(fd[1], "hello\n", 6); 
	//n = read(fd[0], buffer, MAXLINE);
	//write(STDOUT_FILENO, "from parent:", 12);
	//write(STDOUT_FILENO, buffer, n);
	wait(NULL);
	// pipe is not bi-directional.
	// If parent process tries to read as well as write 
	// to pipe, the buffer will be consumed by itself.
    }
    else { /* child */
	close(fd[1]);
	n = read(fd[0], buffer, MAXLINE);
	printf("%d\n", n);
	write(STDOUT_FILENO, buffer, n);
    }
}


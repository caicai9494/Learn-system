#include <common.h>

int main()
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;

    char buf[MAX_LINE];
    char addr[INET_ADDRSTRLEN];

    int ret, i, n;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
	perror("socket");
	exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (ret != 0) {
	perror("bind");
	exit(1);
    }

    ret = listen(listenfd, 20);
    if (ret != 0) {
	perror("listen");
	exit(1);
    }

    printf("Accepting...\n");

    while (1) {
	cliaddr_len = sizeof(cliaddr);
	connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);

	ret = fork();
	if (ret < 0) {
	    perror("fork");
	    exit(1);
	}

	if (ret == 0) { /* child */ 
	    while (1) {
		n = read(connfd, buf, MAX_LINE);
		if (!inet_ntop(AF_INET, &cliaddr.sin_addr, addr, sizeof(addr))) {
		    perror("inet_ntop");
		    exit(1);
		} 
		printf("received from %s at port %d\n", addr, ntohs(cliaddr.sin_port)); 
		
		write(STDOUT_FILENO, buf, n);
		write(connfd, buf, n);
	    }
	    
	}
	else {
	    close(connfd);
	}


    }
}

#include <common.h>

#define CLI_MAX FD_SETSIZE

int main()
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int nready, listenfd, connfd, sockfd;

    char buf[MAX_LINE];
    char addr[INET_ADDRSTRLEN];
    int clients[CLI_MAX];

    int ret, i, n;

    fd_set readfds;
    int maxfd, nfds;
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    FD_ZERO(&readfds);
    for (i = 0; i < CLI_MAX; i++) {
	clients[i] = -1;
    }	

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
	err_exit("socket");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (ret != 0) {
	err_exit("bind");
    }

    ret = listen(listenfd, 20);
    if (ret != 0) {
	err_exit("listen");
    }

    FD_SET(listenfd, &readfds);
    maxfd = listenfd;

    printf("Accepting...\n");

    while (1) {

	nready = select(maxfd + 1, &readfds, NULL, NULL, NULL); 

	if (nready < 0) {
	    err_exit("select");
	}
	
	if (FD_ISSET(listenfd, &readfds)) {
	    cliaddr_len = sizeof(cliaddr);
	    connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);

	    if (!inet_ntop(AF_INET, &cliaddr.sin_addr, addr, sizeof(addr))) {
		err_exit("inet_ntop");
	    } 
	    printf("received from %s at port %d\n", addr, ntohs(cliaddr.sin_port)); 

	    for (i = 0; i < CLI_MAX; i++) {
		if (clients[i] == -1) {
		    clients[i] = connfd;
		    break;
		}
	    }
	    if (i == CLI_MAX) {
		fprintf(stderr, "too many clients connection\n");
		exit(1);
	    }
	    FD_SET(connfd, &readfds);

	    maxfd = (connfd > maxfd) ? connfd : maxfd;
	    if (--nready == 0) {
		continue;    
		// no readable clients fd
	    }
	}

	// handle client fd
	for (i = 0; i < CLI_MAX; i++) {

	    sockfd = clients[i];

	    if (sockfd == -1) {
		continue;
	    }

	    if (FD_ISSET(sockfd, &readfds)) {

		n = read(sockfd, buf, MAX_LINE);
		if (n == 0) {
		    close(sockfd);
		    FD_CLR(sockfd, &readfds); 
		    clients[i] = -1;
		}
		else {
		    write(sockfd, buf, n);
		}

	    }

	}

    }
}

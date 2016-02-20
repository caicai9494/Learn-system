#include <common.h>

int main(int argc, char* argv[])
{
    char buf[MAX_LINE];
    struct sockaddr_in servaddr;

    int sockfd, n, ret;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
	perror("socket");
	exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr.s_addr);
    servaddr.sin_port = htons(SERV_PORT);


    ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (ret < 0) {
	perror("connect");
	exit(1);
    }

    while (1) {
	putchar('>');
	n = read(STDIN_FILENO, buf, MAX_LINE);
	write(sockfd, buf, n);

	n = read(sockfd, buf, MAX_LINE);
	write(STDOUT_FILENO, buf, n);
	putchar('\n');
    }

}

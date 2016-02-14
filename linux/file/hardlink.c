#include <common.h>

int main(int argc, char* argv[])
{
    if (3 != argc) {
	printf("usage: tsk file1 file2\n");
	exit(1);
    }

    if (0 != link(argv[1], argv[2])) {
	perror("link");
	exit(1);
    }
    
}

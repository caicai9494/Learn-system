#include <common.h>

int main()
{
    FILE *file;
    int c;

    file = fopen("../text.txt", "r");

    c = fgetc(file);
    if (EOF == c) {
	perror("fgetc");
	exit(1);
    }
    printf("first char %c\n", c);

    c = ungetc('2', file);
    printf("ungetc char %c\n", c);

    c = fgetc(file);
    if (EOF == c) {
	perror("fgetc");
	exit(1);
    }
    printf("after ungetc char %c\n", c);

    // a successful 'fseek' undoes 'fgetc'
    c = fseek(file, 0, SEEK_CUR);
    if (0 != c) {
	perror("fseek");
	exit(1);
    }
    printf("after fseek char %c\n", fgetc(file));
}

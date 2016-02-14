#include <common.h>

int main()
{
    DIR* curdir = opendir("..");
    if (NULL == curdir) {
	perror("opendir");
	exit(-1);
    }

    // iterate through current parent directory
    struct dirent* cursor;
    for (cursor = readdir(curdir); cursor != NULL;) {
	printf("%s\n", cursor->d_name);
	// only 'd_name' is in POSIX standard

	errno = 0;
	cursor = readdir(curdir);
    }	
    if (0 != errno) {
	perror("readdir");
	if (0 != closedir(curdir)) {
	    perror("closedir");
	    exit(-1);
	}
	exit(-1);
    }

    if (0 != closedir(curdir)) {
	perror("closedir");
	exit(-1);
    }

    
}

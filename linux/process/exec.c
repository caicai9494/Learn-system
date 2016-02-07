#include "common.h"

int main()
{
    int ret = 0;

    // 'execl' only returns on failure (-1) ...
    // make sense since the original address space and 
    // image is replaced

    /*
    ret = execl("/usr/bin/vi", "vi", "text.txt", NULL);
    if (-1 == ret) {
	perror("execl");
    }
    */

    // what if 'execl' invoke the process itself.?
    
    /*
    ret = execl("./", "a.out", NULL);
    if (-1 == ret) {
	perror("execl");
    }
    */

    // permission denied???
    
    // what if a local variable is passed as a 
    // parameter of another process?
    int temp = 5;
    ret = execl("/bin/cat", "cat", temp, NULL);
    if (-1 == ret) {
	perror("execl");
    }
    // Bad address
    // umm.. 

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char buf[512];
    int n;
    for(;;) {
	n = read(0, buf, sizeof buf);
	
	if(n == 0) break;
	if(n < 0) {
	    fprintf(stdout, "error\n");
	    exit(1);
	}	
	if(n !=  write(1, buf, n)) {
	    fprintf(stdout, "error\n");
	    exit(1);
	}
    }
    return 0;
}

/* Listing 3.1 (print-pid.c) Printing the Process ID */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("The process ID is %d\n", (int)getpid());
	printf("The parent process ID is %d\n", (int)getppid());
	return 0;
}
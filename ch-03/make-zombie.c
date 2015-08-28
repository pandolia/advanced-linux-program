/* Listing 3.6 (make-zombie.c) Making a Zombie Process */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	if (fork()) {
		sleep(60);
	} else {
		exit(0);
	}

	return 0;
}
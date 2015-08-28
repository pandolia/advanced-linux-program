/* Listing 2.5x (display-error.c) */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int fd = open("inputfile.txt", O_RDONLY);
	if (fd == -1) {
		/* The open failed. Print an error message and exit. */
		fprintf(stderr, "error opening file: %s\n", strerror(errno));
		exit(1);
	};

	close(fd);

	return 0;
}
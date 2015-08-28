/* Listing 5.6 (mmap-read.c) Read an Integer from a Memory-Mapped File,
   and Double it */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define FILE_LENTH 0x100

int main(int argc, char* const argv[]) {
	int fd;
	void* file_memory;
	int integer;

	/* Open the file */
	fd = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
	file_memory = mmap(0, FILE_LENTH, PROT_READ | PROT_WRITE,
								MAP_SHARED, fd, 0);
	close(fd);

	/* Read the integer, print it out, and double it. */
	sscanf(file_memory, "%d", &integer);
	printf("value: %d\n", integer);
	sprintf((char*)file_memory, "%d\n", 2 * integer);

	/* Release the memory (unnecessary because the program exits). */
	munmap(file_memory, FILE_LENTH);

	return 0;
}
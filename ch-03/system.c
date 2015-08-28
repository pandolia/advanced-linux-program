/* Listing 3.2 (system.c) Using the system Call */
/*
#include <stdio.h>
#include <unistd.h>
*/
#include <stdlib.h>

int main(int argc, char *argv[]) {
	return system("ls -l");
}
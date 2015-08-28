/* Listing 2.3 (print-env.c) Printing the Execution Environment */

#include <stdio.h>

/* The ENVIRON variable contains the environment */
extern char** environ;

int main(int argc, char *argv[]) {
	for(char **var = environ; *var != NULL; ++var) {
		printf("%s\n", *var);
	}

	return 0;
}
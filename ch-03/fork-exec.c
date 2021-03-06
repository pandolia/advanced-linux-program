/* Listing 3.4 (fork-exec.c) Using fork and exec Together */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* Spawn a child process running a new program. PROGRAM is the name
   of the program to run; the path will be searched for this program.
   ARG_LIST is a NULL-terminated list of character strings to be passed
   as the program's argument list. Returns the process ID of the spawned
   process. */
int spawn(char *program, char** arg_list) {
	pid_t child_pid;

	/* Duplicate this process. */
	child_pid = fork();
	if (child_pid != 0) {
		/* This is the parent process. */
		return child_pid;
	} else {
		/* Now execute PROGRAM, searching for it in the path. */
		execvp(program, arg_list);
		/* The execvp function returns only if an error occurs. */
		fprintf(stderr, "an error occurred in execvp\n");
		abort();
	}
}


int main(int argc, char *argv[]) {
	/* The argument list to pass to the "ls" command. */
	char* arg_list[] = {
		"ls",		/* argv[0], the name of the program. */
		"-l",
		NULL		/* The argument list must end with a NULL. */
	};

	/* Spawn a child process running the "ls" command. Ignore the
	   returned child process ID. */
	spawn("ls", arg_list);

	/* Wait for the child process to complete. */
	int child_status;
	wait(&child_status);
	if (WIFEXITED(child_status)) {
		printf("the child process exited normally,"
			   "with exit code %d\n",
			   WEXITSTATUS(child_status));
	} else {
		printf("the child procee exited abnormally\n");
	}

	return 0;
}
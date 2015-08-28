/* Listing 3.7 (sigchld.c) Cleaning Up Children by Handling SIGCHLD */

#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

sig_atomic_t child_exit_status;

void clean_up_child_process(int signal_number) {
	/* Clean up the child process. */
	int status;
	wait(&status);
	/* Store its exit status in a global variable. */
	child_exit_status = status;
}

int main(int argc, char *argv[]) {
	/* Handle SIGCHILD by calling clean_up_child_process. */
	struct sigaction sigchld_action;
	memset(&sigchld_action, 0, sizeof(sigchld_action));
	sigchld_action.sa_handler = &clean_up_child_process;
	sigaction(SIGCHLD, &sigchld_action, NULL);

	/* Now do things, including forking a child process. */
	if (fork()) {
		sleep(3);
	} else {
		exit(115);
	}

	if (WIFEXITED(child_exit_status)) {
		printf("the child process exited normally, "
			   "with exit code %d\n",
			   WEXITSTATUS(child_exit_status));
	} else {
		printf("the child procee exited abnormally\n");
	}

	return 0;
}
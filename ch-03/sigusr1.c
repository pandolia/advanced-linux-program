/* Listing 3.5 (sigusr1.c) Using a Signal Handler */

/* compile and run this file, 
   and press Ctrl+C three times,
   or run "kill -INT pid" in shell three times*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

sig_atomic_t sigint_count = 0;

void handler(int signal_number) {
	++sigint_count;
}

int main(int argc, char *argv[]) {
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handler;

	sigaction(SIGINT, &sa, NULL);

	sig_atomic_t prev = sigint_count;
	while (prev < 3) {
		sleep(100);
		if (prev != sigint_count) {
			prev = sigint_count;
			fprintf(stderr, "Received %-2d SIGINT\n", prev);
		}
	}
	
	return 0;
}
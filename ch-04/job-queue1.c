// Listing 4.10 (job-queue1.c) Thread Function to Process Jobs from the Queue

#include <malloc.h>

struct job {
	/* Link field for linked list. */
	struct job* next;

	/* Other fields describing work to be done... */
};

/* A linked list of pending jobs. */
struct job* job_queue;

/* Process queued jobs until the queue is empty. */
void *thread_function(void *arg) {
	while (job_queue != NULL) {
		/* Get the next available job. */
		struct job* next_job = job_queue;

		/* Remove this job from the list. */
		job_queue = job_queue->next;

		/* Carry out the work. */
		process_job(next_job);

		/* Clean up. */
		free(next_job);
	}
	return NULL;
}
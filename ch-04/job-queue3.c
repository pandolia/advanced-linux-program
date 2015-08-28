// Listing 4.12 (job-queue3.c) Job Queue Controlled by a Semaphore

#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>

struct job {
	/* Link field for linked list. */
	struct job* next;

	/* Other fields describing work to be done... */
};

/* A linked list of pending jobs. */
struct job* job_queue;

/* A mutex protecting job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/* A semaphore counting the number of jobs in the queue. */
sem_t job_queue_count;

/* Perform one-time initialization of the job queue. */
void initialize_job_queue() {
	/* The queue is initially empty. */
	job_queue = NULL;

	/* Initialize the semaphore which counts jobs in the queue. Its
	   initial value should be zero. */
	sem_init(&job_queue_count, 0, 0);
}

/* Process queued jobs until the queue is empty. */
void *thread_function(void *arg) {
	while (job_queue != NULL) {
		struct job* next_job;

		/* Wait on the job queue semapthore. If its value is positive,
		   indicating that the queue is not empty, decrement the count by 1.
		   If the queue is empty, block until a new job is enqueued. */
		sem_wait(&job_queue_count);

		/* Lock the mutex on the job queue. */
		pthread_mutex_lock(&job_queue_mutex);

		/* Now it's safe to check if the queue is empty. */
		if (job_queue == NULL) {
			next_job = NULL;
		} else {
			/* Get the next available job. */
			next_job = job_queue;
			/* Remove this job from the list. */
			job_queue = job_queue->next;
		}

		/* Unlock the mutex on the job queue because we're done with the
		   queue for now. */
		pthread_mutex_unlock(&job_queue_mutex);

		/* Was the queue empty? If so, end the thread. */
		if (next_job == NULL) {
			break;
		}

		/* Carry out the work. */
		process_job(next_job);

		/* Clean up. */
		free(next_job);
	}
	return NULL;
}

/* Add a new job to the front of the job queue. */
void enqueue_job(struct job* new_job) {
	/* Lock the mutex on the job queue before accessing it. */
	pthread_mutex_lock(&job_queue_mutex);

	/* Place the new job at the head of the queue. */
	new_job->next = job_queue;
	job_queue = new_job;

	/* Post to the semapthore to indicate that another job is available.
	   If threads are blocked, waiting on the semphore, one will become unblocked
	   so it can process the job. */
	sem_post(&job_queue_count);

	/* Unlock the job queue mutex. */
	pthread_mutex_unlock(&job_queue_mutex);
}
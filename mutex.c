#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


/* race conditions happen only on multicore cpu, mutex is the way to prevent it*/
int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 10000000; i++) 
	{
        pthread_mutex_lock(&mutex);
        mails++;							// compilation to see assembly code : ggc -S <file_name>.c
        pthread_mutex_unlock(&mutex);

		/* assembly operations during mail++ */
        // read mails
        // increment	 : in the CPU
        // write mails	= increment in the memory
    }
}

int main(int argc, char* argv[]) {
    pthread_t p[4];
	int i;

    pthread_mutex_init(&mutex, NULL);  // pointer to mutex, attributes
	for (i = 0; i < 4; i++)
	{
    	if (pthread_create(p + i, NULL, &routine, NULL) != 0) 
        	return 1;
		printf("Thread %d has started\n", i);
    }

	for (i = 0; i < 4; i++)
	{
    	if (pthread_join(p[i], NULL) != 0)
        	return 2;
		printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
}
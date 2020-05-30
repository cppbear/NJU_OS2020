#include "lib.h"
#include "types.h"

void producer(sem_t *mutex, sem_t *full, sem_t *empty)
{
	int id = getpid() - 2;
	while (1)
	{
		sem_wait(empty);
		sleep(128);
		sem_wait(mutex);
		sleep(128);
		printf("Producer %d: produce\n", id);
		sleep(128);
		sem_post(mutex);
		sleep(128);
		sem_post(full);
		sleep(128);
	}
}

void consumer(sem_t *mutex, sem_t *full, sem_t *empty)
{
	while (1)
	{
		sem_wait(full);
		sleep(128);
		sem_wait(mutex);
		sleep(128);
		printf("Consumer : consume\n");
		sleep(128);
		sem_post(mutex);
		sleep(128);
		sem_post(empty);
		sleep(128);
	}
}

int main(void)
{
	// TODO in lab4
	printf("bounded_buffer\n");
	sem_t mutex, fullBuffers, emptyBuffers;
	sem_init(&mutex, 1);
	sem_init(&fullBuffers, 0);
	sem_init(&emptyBuffers, 5);

	for (int i = 0; i < 5; i++)
	{
		if (fork() == 0)
		{
			if (i < 4)
			{
				producer(&mutex, &fullBuffers, &emptyBuffers);
			}
			else
			{
				consumer(&mutex, &fullBuffers, &emptyBuffers);
			}
		}
	}

	while (1);
	sem_destroy(&mutex);
	sem_destroy(&fullBuffers);
	sem_destroy(&emptyBuffers);
	exit();
	return 0;
}

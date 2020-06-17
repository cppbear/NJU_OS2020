#include "lib.h"
#include "types.h"

static unsigned long next = 61;

int myrand()
{
	read(SH_MEM, (uint8_t *)&next, 4, 24);
	next = next * 1103515245 + 12345;
	write(SH_MEM, (uint8_t *)&next, 4, 24);
	return ((unsigned)(next / 65536) % 211) + 53;
}

void producer(sem_t *mutex, sem_t *full, sem_t *empty)
{
	int id = getpid() - 2;
	while (1)
	{
		sem_wait(empty);
		sleep(myrand());
		sem_wait(mutex);
		sleep(myrand());
		printf("Producer %d: produce\n", id);
		sleep(myrand());
		sem_post(mutex);
		sleep(myrand());
		sem_post(full);
		sleep(myrand());
	}
}

void consumer(sem_t *mutex, sem_t *full, sem_t *empty)
{
	while (1)
	{
		sem_wait(full);
		sleep(myrand());
		sem_wait(mutex);
		sleep(myrand());
		printf("Consumer : consume\n");
		sleep(myrand());
		sem_post(mutex);
		sleep(myrand());
		sem_post(empty);
		sleep(myrand());
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
	write(SH_MEM, (uint8_t *)&next, 4, 24);
	int ret = 1;
	for (int i = 0; i < 5; i++)
	{
		if (ret > 0)
			ret = fork();
	}
	int id = getpid();
	if (id > 1 && id < 6)
	{
		sleep(myrand());
		producer(&mutex, &fullBuffers, &emptyBuffers);
	}
	else if (id == 6)
	{
		consumer(&mutex, &fullBuffers, &emptyBuffers);
	}

	while (1);
	sem_destroy(&mutex);
	sem_destroy(&fullBuffers);
	sem_destroy(&emptyBuffers);
	exit();
	return 0;
}

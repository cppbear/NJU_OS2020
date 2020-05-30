#include "lib.h"
#include "types.h"

void writer(sem_t *writemutex)
{
	int id = getpid() - 3 - 2;
	while (1)
	{
		sem_wait(writemutex);
		sleep(128);
		printf("Writer %d: write\n", id);
		sleep(128);
		sem_post(writemutex);
		sleep(128);
	}
}

void reader(sem_t *writemutex, sem_t *countmutex, int *rcount)
{
	int id = getpid() - 2;
	while (1)
	{
		sem_wait(countmutex);
		sleep(128);
		read(SH_MEM, (uint8_t *)rcount, 4, 12);
		if (*rcount == 0)
		{
			sem_wait(writemutex);
			sleep(128);
		}
		read(SH_MEM, (uint8_t *)rcount, 4, 12);
		++(*rcount);
		write(SH_MEM, (uint8_t *)rcount, 4, 12);
		sleep(128);
		sem_post(countmutex);
		sleep(128);
		printf("Reader %d: read, total %d reader\n", id, *rcount);
		sleep(128);
		sem_wait(countmutex);
		sleep(128);
		read(SH_MEM, (uint8_t *)rcount, 4, 12);
		--(*rcount);
		write(SH_MEM, (uint8_t *)rcount, 4, 12);
		sleep(128);
		read(SH_MEM, (uint8_t *)rcount, 4, 12);
		if (*rcount == 0)
		{
			sem_post(writemutex);
			sleep(128);
		}
		sem_post(countmutex);
		sleep(128);
	}
}

int main(void)
{
	// TODO in lab4
	printf("reader_writer\n");
	sem_t writemutex, countmutex;
	sem_init(&writemutex, 1);
	sem_init(&countmutex, 1);
	int rcount = 0;
	write(SH_MEM, (uint8_t *)&rcount, 4, 12);
	
	for (int i = 0; i < 6; i++)
	{
		if (fork() == 0)
		{
			if (i < 3)
			{
				reader(&writemutex, &countmutex, &rcount);
			}
			else
			{
				writer(&writemutex);
			}
		}
	}
	
	while (1);
	sem_destroy(&writemutex);
	sem_destroy(&countmutex);
	exit();
	return 0;
}

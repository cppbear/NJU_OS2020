#include "lib.h"
#include "types.h"

static unsigned long next = 31;

int myrand()
{
	next = next * 1103515245 + 12345;
	return ((unsigned)(next / 65536) % 211) + 23;
}

void mysrand(unsigned seed)
{
	next = seed;
}

void writer(sem_t *writemutex)
{
	int id = getpid() - 3 - 2;
	while (1)
	{
		sem_wait(writemutex);
		sleep(myrand());
		printf("Writer %d: write\n", id);
		sleep(myrand());
		sem_post(writemutex);
		sleep(myrand());
	}
}

void reader(sem_t *writemutex, sem_t *countmutex, int *rcount)
{
	int id = getpid() - 2;
	while (1)
	{
		sem_wait(countmutex);
		sleep(myrand());
		read(SH_MEM, (uint8_t *)rcount, 4, 12);
		if (*rcount == 0)
		{
			sem_wait(writemutex);
			sleep(myrand());
		}
		read(SH_MEM, (uint8_t *)rcount, 4, 12);
		++(*rcount);
		write(SH_MEM, (uint8_t *)rcount, 4, 12);
		sleep(myrand());
		sem_post(countmutex);
		sleep(myrand());
		printf("Reader %d: read, total %d reader\n", id, *rcount);
		sleep(myrand());
		sem_wait(countmutex);
		sleep(myrand());
		read(SH_MEM, (uint8_t *)rcount, 4, 12);
		--(*rcount);
		write(SH_MEM, (uint8_t *)rcount, 4, 12);
		sleep(myrand());
		read(SH_MEM, (uint8_t *)rcount, 4, 12);
		if (*rcount == 0)
		{
			sem_post(writemutex);
			sleep(myrand());
		}
		sem_post(countmutex);
		sleep(myrand());
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
	/*
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
	*/
	int ret = 1;
	for (int i = 0; i < 6; i++)
	{
		if (ret > 0)
			ret = fork();
	}
	int id = getpid();
	if (id > 1 && id < 5)
	{
		mysrand(myrand() + id);
		reader(&writemutex, &countmutex, &rcount);
	}
	else if (id > 4 && id < 8)
	{
		mysrand(myrand() - id);
		writer(&writemutex);
	}

	while (1);
	sem_destroy(&writemutex);
	sem_destroy(&countmutex);
	exit();
	return 0;
}

#include "lib.h"
#include "types.h"

#define N 5

sem_t forks[5];

static unsigned long next = 48;

int myrand()
{
	read(SH_MEM, (uint8_t *)&next, 4, 24);
	next = next * 1103515245 + 12345;
	write(SH_MEM, (uint8_t *)&next, 4, 24);
	return ((unsigned)(next / 65536) % 231) + 83;
}

void philosopher(int i)
{
	int id = getpid() - 2;
	while (1)
	{
		printf("Philosopher %d: think\n", id);
		sleep(myrand());
		if (i % 2 == 0)
		{
			sem_wait(forks + i);
			sleep(myrand());
			sem_wait(forks + ((i + 1) % N));
			sleep(myrand());
		}
		else
		{
			sem_wait(forks + ((i + 1) % N));
			sleep(myrand());
			sem_wait(forks + i);
			sleep(myrand());
		}
		printf("Philosopher %d: eat\n", id);
		sleep(myrand());
		sem_post(forks + i);
		sleep(myrand());
		sem_post(forks + ((i + 1) % N));
		sleep(myrand());
	}
}

int main(void)
{
	// TODO in lab4
	printf("philosopher\n");
	for (int i = 0; i < 5; i++)
	{
		sem_init(forks + i, 1);
	}
	write(SH_MEM, (uint8_t *)&next, 4, 24);
	int ret = 1;
	for (int i = 0; i < 5; i++)
	{
		if (ret > 0)
			ret = fork();
	}
	if (getpid() > 1)
	{
		sleep(myrand());
		philosopher(getpid() - 2);
	}

	while (1);
	for (int i = 0; i < 5; i++)
	{
		sem_destroy(forks + i);
	}
	exit();
	return 0;
}

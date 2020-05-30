#include "lib.h"
#include "types.h"

#define N 5

sem_t forks[5];

void philosopher(int i)
{
	int id = getpid() - 2;
	while (1)
	{
		printf("Philosopher %d: think\n", id);
		sleep(128);
		if (i % 2 == 0)
		{
			sem_wait(forks + i);
			sleep(128);
			sem_wait(forks + ((i + 1) % N));
			sleep(128);
		}
		else
		{
			sem_wait(forks + ((i + 1) % N));
			sleep(128);
			sem_wait(forks + i);
			sleep(128);
		}
		printf("Philosopher %d: eat\n", id);
		sleep(128);
		sem_post(forks + i);
		sleep(128);
		sem_post(forks + ((i + 1) % N));
		sleep(128);
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
	
	for (int i = 0; i < 5; i++)
	{
		if (fork() == 0)
		{
			philosopher(i);
		}
	}

	while (1);
	for (int i = 0; i < 5; i++)
	{
		sem_destroy(forks + i);
	}
	exit();
	return 0;
}

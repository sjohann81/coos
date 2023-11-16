#include <stdio.h>
#include "coos.h"


/* application tasks */

void *task1(void *arg)
{
	static int cont = 0;
	
	printf("task 1, cont: %d\n", cont++);
	
	return 0;
}

void *task2(void *arg)
{
	static int cont = 0;
	
	printf("task 2, cont: %d\n", cont++);
	
	return 0;
}

void *task3(void *arg)
{
	static int cont = 0;
	
	printf("task 3, cont: %d\n", cont++);
	
	return 0;
}


int main(void)
{
	struct task_s tasks[] = {
		{task1, 128, 128},
		{task3, 50, 50},
		{task2, 75, 75}
	};
	struct task_s *ptask;
	
	while (1) {
		for (int i = 0; i < sizeof(tasks) / sizeof(struct task_s); i++) {
			ptask = &tasks[i];
			if (!--ptask->pcounter) {
				ptask->pcounter = ptask->priority;
				ptask->task(0);
			}
		}
	}
	
	/* never reached */
	return 0;
}

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


/* CoOS API */

void task_add(struct task_s *tasks, void *(task_ptr)(void *), unsigned char priority)
{
	struct task_s *ptask;
	int i;
	
	for (i = 0; i < MAX_TASKS; i++) {
		ptask = &tasks[i];
		if (!ptask->task) break;
	}
	
	ptask->task = task_ptr;
	ptask->priority = priority;
	ptask->pcounter = priority;
}

void task_schedule(struct task_s *tasks)
{
	struct task_s *ptask;
	int i;
	
	for (i = 0; i < MAX_TASKS; i++) {
		ptask = &tasks[i];
		if (!ptask->task) break;
		
		if (!--ptask->pcounter) {
			ptask->pcounter = ptask->priority;
			ptask->task(0);
		}
	}
}

int main(void)
{
	struct task_s tasks[MAX_TASKS] = { 0 };
	struct task_s *ptasks = tasks;

	task_add(ptasks, task1, 128);
	task_add(ptasks, task2, 75);
	task_add(ptasks, task3, 50);
	
	while (1) {
		task_schedule(ptasks);
	}
	
	/* never reached */
	return 0;
}

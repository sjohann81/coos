#include <stdio.h>


/* application tasks */

void task1(void)
{
	static int cont = 0;
	
	printf("task 1, cont: %d\n", cont++);
}

void task2(void)
{
	static int cont = 0;
	
	printf("task 2, cont: %d\n", cont++);
}

void task3(void)
{
	static int cont = 0;
	
	printf("task 3, cont: %d\n", cont++);
}


int main(void)
{
	void (*task_sched[])(void) = {task1, task3, task2, task2, task3};
	int i = 0;
	
	while (1) {
		(*task_sched[i++])();
		if (i == sizeof(task_sched) / sizeof(void *)) i = 0;
	}

	/* never reached */
	return 0;
}

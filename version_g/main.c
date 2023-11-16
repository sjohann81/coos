#include <stdio.h>
#include <setjmp.h>
#include "coos.h"

/* application tasks */
void *task1(void *arg);
void *task2(void *arg);
void *task3(void *arg);

void *task3(void *arg)
{
	task_init();

	struct message_s *pmsg;
	int cnt = 300000;

	while (1) {				/* task body */
		printf("[task 3 id: %d %d]\n", task_id(), cnt++);
		if (task_mq_items() > 0) {
			pmsg = task_mq_dequeue();
			printf("received (%d): type: %d, data: %ld\n", task_mq_items(), pmsg->type, (long)pmsg->data);
		}
		task_yield();
	}
}

void *task2(void *arg)
{
	task_init();
	
	int cnt = 200000;

	while (1) {				/* task body */
		printf("[task 2 id: %d %d]\n", task_id(), cnt++);
		task_yield();
	}
}

void *task1(void *arg)
{
	task_init();

	struct message_s msg;
	struct message_s *pmsg = &msg;	
	int cnt = 100000;

	while (1) {				/* task body */
		printf("[task 1 id: %d %d]\n", task_id(), cnt++);
		if ((cnt % 10) == 0) {
			pmsg->type = 0;
			pmsg->data = (void *)123;
			task_mq_enqueue(task3, pmsg);
		}
		task_yield();
	}
}


int main(void)
{
	struct task_s tasks[MAX_TASKS] = { 0 };
	struct task_s *ptasks = tasks;
	
	task_pinit(ptasks);
	task_add(ptasks, task1, 128, 1024);
	task_add(ptasks, task2, 75, 1024);
	task_add(ptasks, task3, 50, 1024);
	sched_init(ptasks);
	
	/* never reached */
	return 0;
}

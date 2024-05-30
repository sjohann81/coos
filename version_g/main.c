#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>
#include "coos.h"

void *t1(void *arg);
void *t2(void *arg);
void *t3(void *arg);
void *t4(void *arg);

void *t1(void *arg)
{
	task_init();
	
	int val = 0;
	struct message_s msg1, msg2;
	char str[50];
	struct message_s *pmsg;
	
	while (1) {
		printf("t1\n");
		
		if (task_mq_items() == 0)
			if (val > 0)
				task_yield();

		printf("task 1 enters...\n");
		
		if (task_mq_items())
			task_mq_dequeue();

		pmsg = &msg1;
		pmsg->data = (void *)(size_t)val;
		task_mq_enqueue(t2, pmsg);
		pmsg = &msg2;
		sprintf(str, "hello %d from t1...", val++);
		pmsg->data = (void *)&str;
		task_mq_enqueue(t3, pmsg);

		task_yield();
	}
}

void *t2(void *arg)
{
	task_init();
	
	struct message_s msg1;
	int val = 200;
	struct message_s *msg;
	
	while (1) {
		printf("t2\n");
		
		if (task_mq_items() > 0) {
			printf("task 2 enters...\n");

			msg = task_mq_dequeue();
			printf("message %d\n", (int)(size_t)msg->data);
			msg = &msg1;
			msg->data = (void *)(size_t)val++;
			task_mq_enqueue(t4, msg);
		}
		
		task_yield();
	}
}

void *t3(void *arg)
{
	task_init();
	
	struct message_s msg1;
	int val = 300;
	struct message_s *msg;
	
	while (1) {
		printf("t3\n");
		
		if (task_mq_items() > 0) {
			printf("task 3 enters...\n");
			
			msg = task_mq_dequeue();
			printf("message: %s\n", (char *)msg->data);
			msg = &msg1;
			msg->data = (void *)(size_t)val++;
			task_mq_enqueue(t4, msg);
		}
	
		task_yield();
	}
}

void *t4(void *arg)
{
	task_init();
	
	struct message_s *msg1, *msg2;
	struct message_s dummy;
	
	while (1) {
		printf("t4\n");
		
		if (task_mq_items() > 1) {
			printf("task 4 enters...\n");

			msg1 = task_mq_dequeue();
			msg2 = task_mq_dequeue();
			printf("messages: %d %d\n", (int)(size_t)msg1->data, (int)(size_t)msg2->data);
			
			usleep(100000);
			
			task_mq_enqueue(t1, &dummy);
		}
		
		task_yield();
	}
}

int main(void)
{
	struct task_s tasks[MAX_TASKS] = { 0 };
	struct task_s *ptasks = tasks;

	/* setup CoOS and tasks */
	task_pinit(ptasks);
	task_add(ptasks, t1, 30, 2048);
	task_add(ptasks, t2, 50, 2048);
	task_add(ptasks, t3, 30, 2048);
	task_add(ptasks, t4, 60, 2048);
	sched_init(ptasks);
	
	/* never reached */
	return 0;
}

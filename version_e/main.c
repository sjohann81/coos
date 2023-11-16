#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <unistd.h>

#define N_TASKS		10

/* kernel data / structures */

jmp_buf context[N_TASKS];
void (*tasks[N_TASKS])(void) = { 0 };
int cur = 0, n_tasks = 0;


/* kernel functions */

void task_yield()
{
#ifdef STACK_EXPLODE
	sleep(1);
#endif

	if (!setjmp(context[cur])) {
		if (n_tasks == ++cur)
			cur = 0;
		longjmp(context[cur], 1);
	}
}

int task_id()
{
	return cur;
}

int task_add(void *task)
{
	tasks[cur++] = task;
	n_tasks++;
	
	return cur - 1;
}

void task_init(int guard_size)
{
	char guard[guard_size];		/* reserve some stack space */
	
	memset((char *)guard, 0x69, guard_size);
	
	if (!setjmp(context[cur])) {
		if (cur > 0)
			(*tasks[--cur])();
	}	
}

void sched_init()
{
	(*tasks[cur-1])();
}


/* application tasks */

#ifdef STACK_EXPLODE
void alloc(int v)
{
	char buf[100];
	
	if (v) {
		memset(buf, 0xff, sizeof(buf));
		alloc(--v);
	}
}
#endif

void task2(void)
{
	task_init(1024);
	
	int cnt = 300000;
#ifdef STACK_EXPLODE
	int i = 0;
#endif

	while (1) {				/* task body */
		printf("[task 2 %d %d]\n", task_id(), cnt++);
#ifdef STACK_EXPLODE
		printf("testing %d...\n", ++i);
		alloc(i);
#endif
		task_yield();
	}
}

void task1(void)
{
	task_init(1024);
	
	int cnt = 200000;
#ifdef STACK_EXPLODE
	int i = 0;
#endif

	while (1) {				/* task body */
		printf("[task 1 %d %d]\n", task_id(), cnt++);
#ifdef STACK_EXPLODE
		printf("testing %d...\n", ++i);
		alloc(i);
#endif
		task_yield();
	}
}

void task0(void)
{
	task_init(1024);
	
	int cnt = 100000;
#ifdef STACK_EXPLODE
	int i = 0;
#endif

	while (1) {				/* task body */
		printf("[task 0 %d %d]\n", task_id(), cnt++);
#ifdef STACK_EXPLODE
		printf("testing %d...\n", ++i);
		alloc(i);
#endif
		task_yield();
	}
}


/* kernel initialization */

int main(void)
{
	task_add(task0);
	task_add(task1);
	task_add(task2);
	sched_init();

	return 0;
}

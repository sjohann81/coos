#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "coos.h"


static struct task_s *ptasks;
static struct task_s *pcurrtask;
static int cur = -1;


/* CoOS API */

/* tasks init, add, schedule and sched init (only called on main or internally) */

void task_pinit(struct task_s *tasks)
{
	ptasks = tasks;
	pcurrtask = 0;
}

void task_add(struct task_s *tasks, void *(task_ptr)(void *), unsigned char priority, unsigned int guard)
{
	struct task_s *ptask;
	int i;
	
	for (i = 0; i < MAX_TASKS; i++) {
		ptask = &tasks[i];
		if (!ptask->task) break;
	}
	ptask->task = task_ptr;
	ptask->guard = guard;
	ptask->priority = priority;
	ptask->pcounter = priority;
	cur++;
}

struct task_s *task_schedule(struct task_s *tasks)
{
	struct task_s *ptask;
	int i;
	
	for (;;) {
		for (i = 0; i < MAX_TASKS; i++) {
			ptask = &tasks[i];
			if (!ptask->task) break;
			
			if (!--ptask->pcounter) {
				cur = i;
				pcurrtask = ptask;
				ptask->pcounter = ptask->priority;
				
				return ptask;
			}
		}
	}
}

void sched_init(struct task_s *tasks)
{
	pcurrtask = &tasks[cur];
	pcurrtask->task((void *)0);
}


/* task operations (called inside tasks) */

void task_init()
{
	pcurrtask = &ptasks[cur];
	
	char guard[pcurrtask->guard];		/* reserve some stack space */
	
	memset((char *)guard, 0x69, pcurrtask->guard);
	
	if (!setjmp(pcurrtask->context)) {
		if (cur > 0) {
			pcurrtask = &ptasks[--cur];
			pcurrtask->task((void *)0);
		}
	}	
}

void task_yield()
{
	struct task_s *ptask;
	
	if (!setjmp(pcurrtask->context)) {
		ptask = task_schedule(ptasks);
		longjmp(ptask->context, 1);
	}
}

int task_id()
{
	return cur;
}

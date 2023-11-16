#define MAX_TASKS	20		/* maximum number of tasks */

/* task data structure and pointers */
struct task_s {
	void *(*task)(void *);
	jmp_buf context;
	unsigned int guard;
	unsigned char priority;
	unsigned char pcounter;
};


/* CoOS API */

/* tasks init, add and schedule (only called on main) */
void task_pinit(struct task_s *tasks);
void task_add(struct task_s *tasks, void *(task_ptr)(void *),
	unsigned char priority, unsigned int guard);
struct task_s *task_schedule(struct task_s *tasks);
void sched_init();
void task_init();
void task_yield();
int task_id();

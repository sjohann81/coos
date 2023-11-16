#define MAX_TASKS	20		/* maximum number of tasks */

struct task_s {
	void *(*task)(void *);
	unsigned char priority;
	unsigned char pcounter;
};

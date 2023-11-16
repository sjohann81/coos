struct task_s {
	void *(*task)(void *);
	unsigned char priority;
	unsigned char pcounter;
};

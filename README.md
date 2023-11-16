# CoOS

This is a collection of simple mechanisms to implement task / multiprogramming abstractions without an OS or RTOS support. Bare metal or embedded applications generally rely on a superloop servicing several tasks, implemented as functions (background tasks) and ISRs (foreground tasks) and this is an alternative to the traditional approach.

The ideas presented here perform multitasking cooperatively, so thread safety is less of an issue compared to systems that rely on preemptive scheduling. No need for synchronization primitives (such as mutexes, spinlocks and semaphores) and atomic operations are a great advantage when developing systems based on this concept. Another advantage is that a basic scheduler sometimes is all that is needed to implement manageble embedded software (such as firmware), while using a minimum of additional resources.

In order to guarantee portability for any embedded system and to keep resource usage low, all data structures are allocated statically. Another advantage of this approach is determinism, which is hard to achieve with dynamic memory allocations. On stackless coroutines (versions A to D), data structures allocated inside functions (tasks) should be daclared as *static* if they have to persist after performing their job. Stackful coroutines, such as versions E to G, yield voluntarily to the scheduler and their local data structures persist on the stack.

## Version A - coroutines with static scheduling

## Version B - coroutines with task priorities

## Version C - coroutines with task priorities (structured)

## Version D - coroutines with task priorities and message queues (final version)

## Version E - stackful coroutines

## Version F - stackful coroutines with task priorities (structured)

## Version G - stackful coroutines with task priorities and message queues (final version)

/*
 *  linux/mykernel/mypcb.h
 *
 *  Kernel internal PCB types
 *
 *  Copyright (C) 2013  Mengning
 *
 */

 #define MAX_TASK_NUM 10
 #define KERNEL_STACK_SIZE 1024*8

 /* CPU-specific state of this task */
struct Thread {
    unsigned int  ip;
    unsigned int  sp;
};

typedef struct PCB{
    int pid;
    volatile int state;    /* -1 unrunnable, 0 runnable, >0 stopped */
    unsigned int stack[KERNEL_STACK_SIZE];
    /* CPU-specific state of this task */
    struct  Thread thread;
    unsigned int   task_entry;
    struct  PCB *next;
} tPCB;

 void my_schedule(void);

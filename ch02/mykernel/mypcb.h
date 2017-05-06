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
    /*
     * since we will build 32-bit kernel (which we already specify in `menuconfig`),
     * we also can `unsigned int` which is 32-bit too.
     */
    unsigned long  ip; // 32-bit = 4-byte
    unsigned long  sp;
};

typedef struct PCB{
    int pid;
    volatile long state;    /* -1 unrunnable, 0 runnable, >0 stopped */
    unsigned long stack[KERNEL_STACK_SIZE];
    /* CPU-specific state of this task */
    struct  Thread thread;
    unsigned long   task_entry;
    struct  PCB *next;
} tPCB;

 void my_schedule(void);

/*
 * cooperative_scheduler.h
 *
 * Created: 2014-11-12 17:58:22
 *  Author: Adrian Mrowiec
 */ 


#ifndef COOPERATIVE_SCHEDULER_H_
#define COOPERATIVE_SCHEDULER_H_


#define MAX_NUMBER_OF_TASKS 8

#define NULL 0

typedef void (*func_ptr)(void*);

void AddTask(int priority,int period,func_ptr ptr,void* params);
void execute();
void schedule();
void init_scheduler();



#endif /* COOPERATIVE_SCHEDULER_H_ */

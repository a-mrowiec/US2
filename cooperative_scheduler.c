/*
 * cooperative_scheduler.c
 *
 * Created: 2014-11-05 18:03:23
 *  Author: Adrian Mrowiec
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "cooperative_scheduler.h"

#define FALSE 0
#define TRUE 1

typedef struct{
	func_ptr func;
	int interval;
	int timeLeft;
	char ready;
	void* arg;
} TASK;

static TASK TASKS[MAX_NUMBER_OF_TASKS];

void timer0_init()
{
	TCCR0 |= (1 << WGM01);
	TIMSK |= (1 << OCIE0);

	TCNT0 = 0;
	
	OCR0 = 250;
	
	TCCR0 |= (1 << CS01) | (1<<CS00);
}

void schedule()
{
	cli();
	for(int i=0;i<MAX_NUMBER_OF_TASKS;++i){
		if(--TASKS[i].timeLeft == 0){
			TASKS[i].timeLeft = TASKS[i].interval;
			TASKS[i].ready = TRUE;
		}
	}
	sei();
}

void clear_task(int i)
{
	TASKS[i].func = NULL;
	TASKS[i].arg = NULL;
	TASKS[i].ready = FALSE;
}

void init_scheduler()
{
	for(int i=0;i<MAX_NUMBER_OF_TASKS;++i){
		clear_task(i);
	}
}

void AddTask(int priority,int period,func_ptr ptr,void* params)
{
	if(priority < MAX_NUMBER_OF_TASKS){
		TASK t;
		t.arg = params;
		t.interval = period;
		t.timeLeft = period;
		t.ready = FALSE;
		TASKS[priority] = t;
	}
}

void execute()
{
	timer0_init();
	sei();
	while(1){
		for(int i=0;i<MAX_NUMBER_OF_TASKS;++i){
			if(TASKS[i].ready == TRUE && TASKS[i].func != NULL){
				
				
				(*TASKS[i].func)(TASKS[i].arg);
				TASKS[i].ready = FALSE;
				
				break;
			}
		}
	}
}

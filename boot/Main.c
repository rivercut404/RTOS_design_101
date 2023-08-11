#include "stdint.h"
#include "HalUart.h"
#include "stdbool.h"
#include "HalTimer.h"
#include "task.h"
#include "Kernel.h"
#include "Timer.h"

#include "HalUart.h"
#include "HalInterrupt.h"
#include "stdio.h"
#include "stdlib.h"

static void Hw_init(void);
// static void Printf_test(void);
// static void Timer_test(void);
static void Kernel_init(void);

// User task function declaration 
void User_task0(void);
void User_task1(void);
void User_task2(void);

void main(void) {
    Hw_init();

    Kernel_init();

    while (true);
}

static void Hw_init(void) {
    Hal_interrupt_init();
    Hal_uart_init();
    Hal_timer_init();
}

static void Kernel_init(void) {
    uint32_t taskId;

	Kernel_task_init();

	taskId = Kernel_task_create(User_task0);
	if (NOT_ENOUGH_TASK_NUM == taskId)
	    putstr("Task0 creation fail\n");

	taskId = Kernel_task_create(User_task1);
	if (NOT_ENOUGH_TASK_NUM == taskId)
	    putstr("Task1 creation fail\n");

    taskId = Kernel_task_create(User_task2);
	if (NOT_ENOUGH_TASK_NUM == taskId)
	    putstr("Task2 creation fail\n");

	Kernel_start();
}

void User_task0(void) {
    if (Kernel_get_task_state() == NOT_RUNNING)
        Kernel_yield();

    uint32_t local = 0;

	while (true) {
        delay(100);
	    debug_printf("User task #0 Stack pointer: 0x%x\n", &local);
	}
}

void User_task1(void) {
    if (Kernel_get_task_state() == NOT_RUNNING)
        Kernel_yield();

    uint32_t local = 1;

	while (true) {
        delay(100);
        debug_printf("User task #1 Stack pointer: 0x%x\n", &local);
	}
}

void User_task2(void) {
    if (Kernel_get_task_state() == NOT_RUNNING)
        Kernel_yield();

    uint32_t local = 2;

	while (true) {
        delay(100);
        debug_printf("User task #2 Stack pointer: 0x%x\n", &local);
    }
}

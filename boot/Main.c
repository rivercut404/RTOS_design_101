#include "stdint.h"
#include "HalUart.h"
#include "stdbool.h"
#include "HalTimer.h"
#include "task.h"
#include "Kernel.h"
#include "event.h"

#include "HalUart.h"
#include "HalInterrupt.h"
#include "stdio.h"
#include "stdlib.h"

static void Hw_init(void);
static void Printf_test(void);
static void Timer_test(void);
static void Kernel_init(void);

// User task function declaration 
void User_task0(void);
void User_task1(void);
void User_task2(void);

void main(void) {
    Hw_init();

    uint32_t i = 100;
    while (i--) {
        Hal_uart_put_char('N');
    }
    Hal_uart_put_char('\n');

    putstr("Hello World!\n");

    Printf_test();

	Timer_test();

    Kernel_init();

    while (true);
}

static void Hw_init(void) {
    Hal_interrupt_init();
    Hal_uart_init();
    Hal_timer_init();
}

static void Printf_test(void) {
    char *str = "printf pointer test";
    char *nullptr = 0;
    uint32_t i = 5;
    uint32_t *sysctrl0 = (uint32_t*)0x10001000;

    debug_printf("%s\n", "Hello printf");
    debug_printf("output string pointer: %s\n", str);
    debug_printf("%s is null pointer, %u number\n", nullptr, 10);
    debug_printf("%u = 5\n", i);
    debug_printf("dec=%u hex=%x\n", 0xff, 0xff);
    debug_printf("print zero %u\n", 0);

	debug_printf("SYSCTRL0: %x\n", *sysctrl0);
}

static void Timer_test(void) {
    debug_printf("current count: %u\n", Hal_timer_get_1ms_counter());
    delay(1000);
    debug_printf("current count: %u\n", Hal_timer_get_1ms_counter());
    delay(1000);
    debug_printf("current count: %u\n", Hal_timer_get_1ms_counter());
    delay(1000);
    debug_printf("current count: %u\n", Hal_timer_get_1ms_counter());
    delay(1000);
    debug_printf("current count: %u\n", Hal_timer_get_1ms_counter());
}

static void Kernel_init(void) {
    uint32_t taskId;

	Kernel_task_init();
    Kernel_event_flag_init();

	taskId = Kernel_task_create(User_task0);
	if (NOT_ENOUGH_TASK_NUM == taskId)
	    putstr("Task0 creation fail\n");

	taskId = Kernel_task_create(User_task1);
	if (NOT_ENOUGH_TASK_NUM == taskId)
	    putstr("Task1 creation fail\n");

	Kernel_start();
}

void User_task0(void) {
    uint32_t local = 0;
    debug_printf("User task #0 Stack pointer: 0x%x\n", &local);

	while (true) {
        KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_UartIn);
        switch (handle_event)
        {
        case KernelEventFlag_UartIn:
            debug_printf("\nUartIn Event handled by Task0\n");
			Kernel_send_events(KernelEventFlag_CmdIn);
            break;  
        }
		Kernel_yield();
	}
}

void User_task1(void) {
    uint32_t local = 1;
    debug_printf("User task #1 Stack pointer: 0x%x\n", &local);

	while (true) {
		KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_CmdIn);
		switch (handle_event)
		{ 
		case KernelEventFlag_CmdIn: 
            debug_printf("CmdIn Event handled by Task1\n");
			break;
		}
		Kernel_yield();
	}
}

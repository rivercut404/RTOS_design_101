#include "stdint.h"
#include "Timer.h"
#include "HalTimer.h"
#include "HalInterrupt.h"
#include "task.h"

#include "HalUart.h"
#include "stdio.h"

extern volatile Timer_t *Timer;

static void interrupt_handler(void);

static uint32_t internal_1ms_counter;

void Hal_timer_init(void) {
    // interface reset
	Timer->timerxcontrol.bits.TimerEn = 0;
    Timer->timerxcontrol.bits.TimerMode = 0;
    Timer->timerxcontrol.bits.OneShot = 0;
    Timer->timerxcontrol.bits.TimerSize = 0;
    Timer->timerxcontrol.bits.TimerPre = 0;
    Timer->timerxcontrol.bits.IntEnable = 1;

	Timer->timerxload = 0;
	Timer->timerxvalue = 0xFFFFFFFF;

	// Set periodic mode
	Timer->timerxcontrol.bits.TimerMode = TIMER_PERIODIC;
	Timer->timerxcontrol.bits.TimerSize = TIMER_32BIT_COUNTER;
	Timer->timerxcontrol.bits.OneShot = 0;
	Timer->timerxcontrol.bits.TimerPre = 0;  // Timer prescale bit
	Timer->timerxcontrol.bits.IntEnable = 1;

    // Generate the timer interrupt every 100ms 
	uint32_t interval_100ms = (TIMER_1MHZ_INTERVAL/1024) * 10;

	Timer->timerxload = interval_100ms;
	Timer->timerxcontrol.bits.TimerEn = 1;

	internal_1ms_counter = 0;

    // Register Timer interrupt handler 
	Hal_interrupt_enable(TIMER_INTERRUPT);
	Hal_interrupt_register_handler(interrupt_handler, TIMER_INTERRUPT);
}

static void interrupt_handler(void) {
    // internal_1ms_counter++;

	// Call kernel to switch user task 
	debug_printf("Timer has been expired");
	Kernel_task_scheduler();  // context switching
	Timer->timerxintclr = 1;
}

uint32_t Hal_timer_get_1ms_counter(void) {
    return internal_1ms_counter;
}

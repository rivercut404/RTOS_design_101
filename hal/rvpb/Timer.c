#include "stdint.h"
#include "Timer.h"
#include "HalTimer.h"
#include "HalInterrupt.h"
#include "task.h"
#include "Kernel.h"

#include "HalUart.h"
#include "stdio.h"
#include "stdlib.h"

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
	uint32_t interval_10ms = TIMER_10HZ_INTERVAL / 10;
	Timer->timerxload = interval_10ms;
	Timer->timerxcontrol.bits.TimerEn = 1;

	internal_1ms_counter = 0;

    // Register Timer interrupt handler 
	Hal_interrupt_enable(TIMER_INTERRUPT);
	Hal_interrupt_register_handler(interrupt_handler, TIMER_INTERRUPT);
}

static void interrupt_handler(void) {
    internal_1ms_counter++;

	// debug_printf("timer interrupt has been occured!");

	// Call kernel API to switch user task 
	Timer->timerxintclr = 1;
    // if (((internal_1ms_counter % 10) == 0) && (internal_1ms_counter > 1000)) {
	//     debug_printf("Timer has been expired!!");
	    // Kernel_timer_expired();  
		// If Kernel API for context switching is called in ISR, then LR is set to 0
		// So... maybe because of that the reset handler is executed after the context switching
	// }
}

uint32_t Hal_timer_get_1ms_counter(void) {
    return internal_1ms_counter;
}

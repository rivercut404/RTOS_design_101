#include "stdint.h"
#include "stdbool.h"
#include "memio.h"

#include "task.h"
#include "Kernel.h"

void Kernel_start(void) {
    Kernel_task_start();
}

void Kernel_yield(void) {
    Kernel_task_scheduler();
}

/* cf. Other implementation (pseudo code) that has destination task when sending signals
void send_signal(tcb_t *dest_tcb, uint32_t signal) 
    uint32_t temp_signal = 0; 
	temp_signal = dest_tcb->receive_signal;
	dest_tcb->receive_signal = dest_tcb->receive_signal | signal; 

	if (dest_tcb->wait_signal & signal) == 0
	    dest_tcb->wait_signal = 0;
		context switching or continue executing
*/
void Kernel_send_events(uint32_t event_list) {
    for (uint32_t i=0; i<32; i++) {
	    if ((event_list >> i) & 1) {
		    KernelEventFlag_t sending_event = KernelEventFlag_Empty;
			sending_event = (KernelEventFlag_t)SET_BIT(sending_event, i);
			Kernel_event_flag_set(sending_event);
		}
	}
}

KernelEventFlag_t Kernel_wait_events(uint32_t waiting_list) {
    for (uint32_t i=0; i<32; i++) {
	    if ((waiting_list >> i) & 1) {
		    KernelEventFlag_t waiting_event = KernelEventFlag_Empty;
			waiting_event = (KernelEventFlag_t)SET_BIT(waiting_event, i);

			if (Kernel_event_flag_check(waiting_event)) 
			    return waiting_event;
		}
	}

	return KernelEventFlag_Empty;
}

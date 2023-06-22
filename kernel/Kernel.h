#ifndef KERNEL_KERNEL_H_
#define KERNEL_KERNEL_H_

#include "task.h"

void Kernel_start(void);
void Kernel_yield(void);
void Kernel_timer_expired(void); 

#endif /* KERNEL_KERNEL_H_ */

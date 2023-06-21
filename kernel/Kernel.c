#include "stdint.h"
#include "stdbool.h"

#include "task.h"
#include "Kernel.h"

void Kernel_start(void) {
    Kernel_task_start();
}

void Kernel_yield(void) {
    Kernel_task_scheduler();
}

#ifndef KERNEL_TASK_H_
#define KERNEL_TASK_H_

#include "MemoryMap.h"
#include "stdbool.h"

#define NOT_ENOUGH_TASK_NUM 0xFFFFFFFF

#define USR_TASK_STACK_SIZE 0x100000
#define MAX_TASK_NUM        (TASK_STACK_SIZE / USR_TASK_STACK_SIZE)

#define RUNNING true
#define NOT_RUNNING false

typedef bool task_state_t;

typedef struct KernelTaskContext_t {
    uint32_t spsr;
	uint32_t r0_r12[13];
	uint32_t pc;
} KernelTaskContext_t;

typedef struct KernelTcb_t {
    uint32_t sp;
	task_state_t state; // bool type is 4-Byte size
	uint32_t timeslice; // timeslice for scheduling, default value: 20 
	uint8_t *stack_base;
} KernelTcb_t;

typedef void (*KernelTaskFunc_t) (void);

void Kernel_task_init(void);
void Kernel_task_start(void);
uint32_t Kernel_task_create(KernelTaskFunc_t startFunc);
task_state_t Kernel_get_task_state(void);
void Kernel_task_state_manage(void);
uint32_t Kernel_get_timeslice_value(void);
void Kernel_current_timeslice_decrement(void);
void Kernel_task_context_switching(void);
void Kernel_task_scheduler(void);

#endif /* KERNEL_TASK_H_ */

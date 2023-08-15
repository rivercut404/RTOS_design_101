#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

#include "ARMv7AR.h"
#include "task.h"

static KernelTcb_t sTask_list[MAX_TASK_NUM];
static uint32_t sAllocated_tcb_index;

static uint32_t sCurrent_tcb_index;
static KernelTcb_t *Scheduler_round_robin_algorithm(void);
static void Save_context(void);
static void Restore_context(void);

// Variables for context switching
static KernelTcb_t *sCurrent_tcb;
static KernelTcb_t *sNext_tcb;

void Kernel_task_init(void) {
    sAllocated_tcb_index = 0;  // The number of created user task
	sCurrent_tcb_index = 0;

	for (uint32_t i=0; i<MAX_TASK_NUM; i++) {
	    // Set the sp for user task context
	    sTask_list[i].stack_base = (uint8_t*)(TASK_STACK_START + (i * USR_TASK_STACK_SIZE));
		sTask_list[i].sp = (uint32_t)sTask_list[i].stack_base + USR_TASK_STACK_SIZE - 4;
		sTask_list[i].state = NOT_RUNNING;
		sTask_list[i].timeslice = 20;

		sTask_list[i].sp -= sizeof(KernelTaskContext_t);
		KernelTaskContext_t *ctx = (KernelTaskContext_t*)sTask_list[i].sp;
		ctx->pc = 0;
		ctx->spsr = ARM_MODE_BIT_SYS;  // Set the default mode to SYS
    }
}

void Kernel_task_start(void) {
	sCurrent_tcb = &sTask_list[sCurrent_tcb_index];  // Add for a first context switching
    sNext_tcb = &sTask_list[sCurrent_tcb_index];  // Just for restore starting task
	sCurrent_tcb->state = RUNNING;
	Restore_context();
}

uint32_t Kernel_task_create(KernelTaskFunc_t startFunc) {
    KernelTcb_t *new_tcb = &sTask_list[sAllocated_tcb_index++];

	if (sAllocated_tcb_index > MAX_TASK_NUM) 
        return NOT_ENOUGH_TASK_NUM;
	
	KernelTaskContext_t *ctx = (KernelTaskContext_t*)new_tcb->sp;
	ctx->pc = (uint32_t)startFunc;
	debug_printf("new task has been created. the entry point of the task is %n\n", ctx->pc);

	return (sAllocated_tcb_index - 1);
}	

static KernelTcb_t *Scheduler_round_robin_algorithm(void) {
    sCurrent_tcb_index++;
	sCurrent_tcb_index %= sAllocated_tcb_index;

	return &sTask_list[sCurrent_tcb_index];
}

task_state_t Kernel_get_task_state(void) {
    // functions to check the state of the task before executing
	return sCurrent_tcb->state;
}

void Kernel_task_state_manage(void) {
	sCurrent_tcb->state = NOT_RUNNING;
}

uint32_t Kernel_get_timeslice_value(void) {
	return sCurrent_tcb->timeslice;
}

void Kernel_current_timeslice_decrement(void) {
	sCurrent_tcb->timeslice--;
}

void Kernel_task_scheduler(void) {
    // Set the TCBs
    sCurrent_tcb = &sTask_list[sCurrent_tcb_index];
	sNext_tcb = Scheduler_round_robin_algorithm();

	sNext_tcb->state = RUNNING;

	// Context switching
	Kernel_task_context_switching();
}
	
__attribute__ ((naked)) void Kernel_task_context_switching(void) {
    __asm__ ("B Save_context");
	__asm__ ("B Restore_context");
}

static __attribute__ ((naked)) void Save_context(void) {
	/*
	typedef struct KernelTaskContext_t {
		uint32_t spsr;
		uint32_t r0_r12[13];
		uint_32 pc;
	} KernelTaskContext_t
	
	typedef struct KernelTcb_t {
    uint32_t sp;
	uint8_t *stack_base;
    } KernelTcb_t;
	*/
    // Save current task context into the current task stack 
	__asm__ ("PUSH {lr}");
    __asm__ ("PUSH {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
	__asm__ ("MRS r0, cpsr");
	__asm__ ("PUSH {r0}");

	// Save current task stack pointer into the current TCB
	__asm__ ("LDR r0, =sCurrent_tcb");
	__asm__ ("LDR r0, [r0]");
	__asm__ ("STMIA r0!, {sp}");  // Store Increase After
}

static __attribute__ ((naked)) void Restore_context(void) {
    // Restore next task stack pointer from next TCB 
	__asm__ ("LDR r0, =sNext_tcb");  // sNext_tcb is treated like symbol
	__asm__ ("LDR r0, [r0]");  // Load the address of next tcb 
	__asm__ ("LDMIA r0!, {sp}");

	// Restore next task context from the next task stack 
	__asm__ ("POP {r0}");
	__asm__ ("MSR cpsr, r0");
	__asm__ ("POP {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
	__asm__ ("POP {pc}");
}

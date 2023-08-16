Development Description 

1. Object: Introduction of timeslice as a member variable of TCB for task scheduling

2. Implementation Procedure

  - Add a variable, timeslice, in the TCB (maybe unsigned int32 type)
    - Add timeslice in the TCB
    - Set default value when initializing tasks 
    - Revise the code allocating memory space for TCB
      => This is not needed because the memory space is to be allocated for total TCB struct

  - Coupled with timer interrupt, decrement timeslice value for each time tick
    - In time interrupt ISR, add a function call that decrement current executing task's timeslice value 
      - Add a kernel API function that decrement current executing task's timeslice value: Kernel_current_timeslice_decrement()
      - Add a kernel API function that return the current timeslice value: Kernel_get_timeslice_value()
      - Revise the ISR to call the function that decrement the current timeslice value
  
  - Then... scheduler, Kernel_task_scheduler() function, set the newly executing task's timeslice value (just pre-set value)
    and then run new task! 

3. Issues and Handling

[Aug. 16]
Issue : What if the timer interrupt occur while context switching is ongoing?

- The term "context switching" in this context include the user task state transition to NOT_RUNNING, 
  internal checking of the current task state, call the yield() function.

- One method is that disable the timer interrupt before context switching then enable it after switching
  - It would affect the accuracy of absolute execution time and fairness
  - Let's consider timeslice as just a multiple of the time tick 

  - Mask Timer interrupt while scheduling
  - Disable at the beginning of the scheduler function

  *** Where and When and How to enable it...?
    

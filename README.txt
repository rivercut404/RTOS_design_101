Development Description 

1. Object: Implementation of a preemptive system in conjunction with the timer interrupt

2. Progress: Context switching by using yeild function works well... 
             But, There is some issues in implementing context switching in timer interrupt handler 
             maybe, related to interrupt context.

3. Issue and Conquer

- Introduction of two-state model

- When and Where the state of executing task should be changed? 
  - If timer interrupt occur then the state of the task executing goto NOT_RUNNING (by kernel API)
  
  - At the beginning of each task, Check the state of its own state and if NOT_RUNNING, then yeild
Development Description 

1. Object: Implementation of a preemptive system in conjunction with the timer interrupt

2. Progress: Context switching by using yeild function works well... 
             But, There is some issues in implementing context switching in timer interrupt handler 
             maybe, related to interrupt context. => Resolved!!


3. Issue and Conquer

- Introduction of two-state model

- When and Where the state of executing task should be changed? 
  - If timer interrupt occur then the state of the executing task goto NOT_RUNNING state (by kernel API)
  
  - At the beginning of infinite loop of each task, Check the state of its own state and if NOT_RUNNING, then yeild
      context switching works well... 
      Basic implementation of a preemptive system has been completed! 

  * The first context switching is a little wierd... 0 => 2 rather 0 => 1   
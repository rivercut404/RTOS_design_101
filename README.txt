What I need to check by the test 

1. Does ARM automatically set LR when a interrupt occurs?
  CHECK POINT 
    - User tasks work well when UART/Timer interrupt is enabled
    - It means that the jump and return to/from ISR is executed well
      HOW TO DO TEST?
        1) Revise the timer interrupt code not to cause context switching
        2) Test both interrupt ISR: UART and Timer 

        => task execution goes 0 -> 1 -> 2 then there is no context switching...
        There is context switching but the codes that task execute  is just to call yield function...
        and the jump and return to/from ISR doesn't have any problem (UART, Timer both)
  
  7/18
  CHECK POINT 
    - Check the values of the registers before and after ISR
    - What happens when calling the kernel API in the ISR (UART or Timer)

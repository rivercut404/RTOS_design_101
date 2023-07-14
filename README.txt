What I need to check by the test 

1. Does ARM automatically set LR when a interrupt occurs?
  CHECK POINT 
    - User tasks work well when UART/Timer interrupt is enabled
    - It means that the jump and return to/from ISR is executed well
      HOW TO DO TEST?
        1) Revise the timer interrupt code not to cause context switching
        2) Test both interrupt ISR: UART and Timer 
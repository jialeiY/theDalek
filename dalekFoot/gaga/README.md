[#] 1. refactor Serial port IO
[#] 2. test SPI IO
[#] 3. refactor SPI
[#] 4. test all combination of Prescaler and Period for tim5, to make main tread more efficiency
[ ] 5. circle buffer for usart
[#] 6. disable motor pin on startup to avoid wheel turning on start
[#] 7. read systick counter
[#] 8. can control static speed of motor
[#] 9. control dynamic speed of motor
[#] 10. control speed of motor from SPI
11. the trajectory controlling
[#] 12. output the speed of motor[DoD: output the speed simultaneously via USART, calculate the baudrate] (2)
[#] 13. install all motors
[#] 14. add timer for cycle [DoD: output the time interval between the interrupt] (1)
[#] 15. control the speed of all motors (3)
[#] 16. the architecture of the foot
[#] 17. check board/core/stm32f4xx_it.c:TIM1_BRK_TIM9_IRQHandler() HAL_TIM_IRQHandler(&htim1);
[#] 18. remove __it_transByte_ in i2c
[#] 19. main cycle timer larger than 2ms
[#] 20. no output now.
[#] 21. speed calibration and PID parameter calibration
[#] 22. PID architecture refactoring
[ ] 23. odometry from wheel calculation
[ ] 24. increase the UART speed

# Milestones
1. Trajectory Follower
a. the simplest one, use velocity only
2. communication with RPI using SPI




Motor box design requirements

* speed requirements
output speed = 2000mm/s
output axis speed = 10.98 r / s
motor speed = 300 r /s
==> ratio = 30



* electronic requirements
ADC bit 10bit, range=1024 / r

* dimention
sensor diameter: 20mm, width: 16mm
wheel diameter: 58mm

control requirements
control accuracy: 1mm


==> If sensor attached to wheel shaft directly, the theory of control accuracy is 0.1779mm. So, from the accuracy aspect of view, the position of sensor where it installed doesn't matter.





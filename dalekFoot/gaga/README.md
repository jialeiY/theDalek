[#] 1. refactor Serial port IO
[#] 2. test SPI IO
[#] 3. refactor SPI
[#] 4. test all combination of Prescaler and Period for tim5, to make main tread more efficiency
[ ] 5. circle buffer for usart
[ ] 6. disable motor pin on startup to avoid wheel turning on start
[#] 7. read systick counter



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





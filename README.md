STM32F0-SR04
============

STM32F0 plus HC-SR04 ultrasonic sensor

A very memoriable summer. 

The sensor is easy but not funny in Arduino. It is funny when I was playing it in STM32F0 board in last summer.
A lot of fun with this sensor.


I think pin connections are already shown in the main.c. Other libraries for me are different from you but you will understand
once you read the main.c.

For this particular sensor HC-SR04,  F0 is better than F1 for accurary and range display in LCD ILI9325/9320, and well, I did
use F4 to talk to the sensor, I neede to stop FPU in order to display right float number in ILI9325, which is so frustrated.

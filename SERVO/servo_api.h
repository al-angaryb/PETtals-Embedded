#ifndef servo_api_h
#define servo_api_h

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define CLOCK_DIV 64
#define WRAP 39062
#define FREQ 50


/**
 * @brief Set the position of the servo from 0 to 180 degrees
 * 
 * @param servoPin the GPIO pin the servo is driven by
 * @param angle The position of the servo in degrees
 */
void servoSetPos(int servoPin, float angle);

/**
 * @brief Initialize the pico to run a servo 
 * 
 * @param servoPin the GPIO pin the servo is driven by
 * @param startAngle The starting position of the servo
 */
void servoInit(int servoPin, uint startAngle);



// uint pwm_set_freq_duty(uint slice_num, uint chan, uint freq, int dutCyc);
// void setMillis(int servoPin, float millis);
// void setServo(int servoPin, float startMillis);

#endif




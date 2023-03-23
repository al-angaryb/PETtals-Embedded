#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

float clockDiv = 64;
float wrap = 39062;

/**
 * @brief servoSetPos sets the angular position of a servo running at 50 hz
 * 
 * @param servoPin The gpio pin driving the signal for the servo
 * @param microS The duration of the duty cycle indicating the direction of the servo
 */
void servoSetPos (int servoPin, float microS) {
    pwm_set_gpio_level(servoPin, (microS/20000.f)*39062.f);
}



uint pwm_set_freq_duty(uint slice_num, uint chan, uint freq, int dutCyc) {
    uint clock = 125000000;
    double divider = (clock/freq/4096);
    if (divider / 16 < 1) {
        divider = 1;
    } else {
        divider = divider/16;
    }
    
    uint wrap = (clock / divider) / (freq - 1); 
    //pwm_set_clkdiv(slice_num, divider);
    //pwm_set_wrap(slice_num, wrap);
    //pwm_set_chan_level(slice_num, chan, wrap * (dutCyc / 100));
    pwm_config config = pwm_get_default_config();

    pwm_config_set_clkdiv(&config, divider);
    pwm_config_set_wrap(&config, wrap);
    pwm_init(slice_num, &config, true);
    servoSetPos(0, 400);
    return wrap;
}

/*void servo_set_position(uint slice_num, uint chan, uint angle) {
     if (angle <= 180 && angle >= 0) {
         int freq = 50;
         //Duty cycle range: 12.5% -> 2%
         int dutyCycle = 12;
         pwm_set_freq_duty(slice_num, chan, freq, dutyCycle);
         pwm_set_enabled(slice_num, true);
     }
}*/




void servoInit(int servoPin, uint startAngle) {

    gpio_set_function(servoPin,GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(servoPin);
    uint channel = pwm_gpio_to_channel(servoPin);
    
    pwm_set_freq_duty(slice_num, channel, 50, 2);
    //pwm_set_enabled(slice_num, true);
}

void setMillis(int servoPin, float millis) {
    pwm_set_gpio_level(servoPin, (millis/20000.f)*39062.f);
}

void setServo(int servoPin, float startMillis)
{
    gpio_set_function(servoPin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(servoPin);

    pwm_config config = pwm_get_default_config();
    
    uint64_t clockspeed = clock_get_hz(5);
    clockDiv = 64;
    wrap = 39062;

    while (clockspeed/clockDiv/50 > 65535 && clockDiv < 256) clockDiv += 64; 
    wrap = clockspeed/clockDiv/50;

    pwm_config_set_clkdiv(&config, clockDiv);
    pwm_config_set_wrap(&config, wrap);

    pwm_init(slice_num, &config, true);

    setMillis(servoPin, startMillis);
}
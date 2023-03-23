#include "servo_api.h"

// float clockDiv = 64;
// float wrap = 39062;
// int freq = 50; //driving frequency for servo 50 Hz



void servoSetPos (int servoPin, float angle) {
    if(angle <= 180 && angle >= 0){
        float microS = 11.67*(angle) + 100; 
        pwm_set_gpio_level(servoPin, (microS/20000.f)*WRAP);
    }
}


void servoInit(int servoPin, uint startAngle) {
    
    gpio_set_function(servoPin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(servoPin);
    uint channel = pwm_gpio_to_channel(servoPin);
    pwm_config config = pwm_get_default_config();
    
    uint64_t clockspeed = clock_get_hz(5);

    double divider = (clockspeed/FREQ/4096);
    int wrap = (clockspeed/divider) / (FREQ - 1);

    pwm_config_set_clkdiv(&config, divider);
    pwm_config_set_wrap(&config, WRAP);
    pwm_init(slice_num, &config, true);

    // set start position here
    servoSetPos(servoPin, startAngle);
    sleep_ms(100);
}




// uint pwm_set_freq_duty(uint slice_num, uint chan, uint freq, int dutCyc) {
//     uint clock = 125000000;
//     double divider = (clock/freq/4096);
//     if (divider / 16 < 1) {
//         divider = 1;
//     } else {
//         divider = divider/16;
//     }
    
//     uint wrap = (clock / divider) / (freq - 1); 
//     pwm_config config = pwm_get_default_config();

//     pwm_config_set_clkdiv(&config, divider);
//     pwm_config_set_wrap(&config, wrap);
//     pwm_init(slice_num, &config, true);
//     servoSetPos(0, 400);
//     return wrap;
// }

// void setMillis(int servoPin, float millis) {
//     pwm_set_gpio_level(servoPin, (millis/20000.f)*39062.f);
// }

// void setServo(int servoPin, float startMillis) {
//     gpio_set_function(servoPin, GPIO_FUNC_PWM);
//     uint slice_num = pwm_gpio_to_slice_num(servoPin);

//     pwm_config config = pwm_get_default_config();
    
//     uint64_t clockspeed = clock_get_hz(5);
//     clockDiv = 64;
//     wrap = 39062;

//     while (clockspeed/clockDiv/50 > 65535 && clockDiv < 256) clockDiv += 64; 
//     wrap = clockspeed/clockDiv/50;

//     pwm_config_set_clkdiv(&config, clockDiv);
//     pwm_config_set_wrap(&config, wrap);

//     pwm_init(slice_num, &config, true);

//     setMillis(servoPin, startMillis);
// }
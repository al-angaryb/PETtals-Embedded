#include <stdio.h>
#include "pico/stdlib.h"
#include "Servo_API.c"
#include "hardware/irq.h"

//Servo Range (500us - 2500us) -> (2kHz - 400Hz)
#define BUTTON_PIN 8

bool direction = true;
double currentMillis = 1;
int servoPin = 0;


int main() {
    stdio_init_all();
    servoInit(servoPin, 90);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    bool locked = false;
    int angle = 0;
    while(true) {
        



        if(gpio_get(BUTTON_PIN) != 0) {
            printf("Unlocked\n");
            servoSetPos(servoPin, 20);
            locked = false;
            sleep_ms(100);
            // if(locked == true) {
                
            // } else {
            //     servoSetPos(servoPin, 90);
                
            // }
            
        }
        if(gpio_get(BUTTON_PIN) == 0) {
            printf("Locked\n");
            servoSetPos(servoPin, 80);
            locked = true;
            sleep_ms(100);
            
        }



        // if (angle == 180) {
        //     angle = 0;
        //     printf("Servo Flips\n");
        //     sleep_ms(100);
        // }
        // servoSetPos(servoPin, angle);
        // sleep_ms(100);
        // angle = angle + 5; 
    }



    return 0;

}


#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "Servo_API.c"
#include "ping.h"
//#include "wolfssl/ssl.h"


bool direction = true;
double currentMillis = 1;
int servoPin = 0;
int pirPin = 1;
int pirState = false;
int servoOpenAngle = 0;
int servoClosedAngle = 180;

void led_task()
{   
    while (true) {
        printf("I am printing \n");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
    }
}

void pir_task(){
    while(true){
        pirState = gpio_get(pirPin);
        if(pirState != false){
            servoSetPos(servoPin, servoOpenAngle);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            if(pirState == false){
                printf("Motion detected. ");
                pirState = true;
            }
        } else {
            servoSetPos(servoPin, servoClosedAngle);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
            if(pirState != false){
                printf("Motion ended. ");
                pirState = false; 
            }
        }
    }
}

void servo_task(){
    int angle = 0;
    while(true) {
        if (angle == 180) {
            angle = 0;
            printf("Servo Flips\n");
            sleep_ms(100);
        }
        servoSetPos(servoPin, angle);
        sleep_ms(100);
        angle = angle + 5; 
    }
}

void ping_task(){
    cyw43_arch_enable_sta_mode();
    printf("Connecting to WiFi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("failed to connect.\n");
        exit(1);
    } else {
        printf("Connected.\n");
    }

    ip_addr_t ping_addr;
    ip4_addr_set_u32(&ping_addr, ipaddr_addr(PING_ADDR));
    ping_init(&ping_addr);

    while(true) {
        vTaskDelay(100);
    }

    cyw43_arch_deinit();
}

int main()
{
    stdio_init_all();
    servoInit(servoPin, 0);
    gpio_set_function(pirPin, GPIO_IN);

    //portSUPPRESS_TICKS_AND_SLEEP();

    if (cyw43_arch_init()) {
        printf("WiFi init failed");
        return -1;
    }


    //xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    //xTaskCreate(servo_task, "Servo Task", 256, NULL, 1, NULL);
    //xTaskCreate(ping_task, "Ping Task", 256, NULL, 1, NULL );
    xTaskCreate(pir_task, "Motion Detection Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();
    

    while(1){};
}
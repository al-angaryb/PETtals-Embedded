#include "FreeRTOS.h"
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "m6e_uhf_api.h"
#include "servo_api.h"

#define BAUD 115200
#define UART_ID uart1
#define SERVO_PIN 0
#define MOTION_PIN 28
#define M6E_TX 4
#define M6E_RX 5


boolean scanning = false;
uint32_t scanTime = ; //Unit is [] and is the length the M6E will scan for
uint32_t startTime;

bool setupNano(long baudRate) {
    
    sleep_ms(1000);
    uart_init(UART_ID, baudRate);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    sleep_ms(3500);
    begin(UART_ID, UART_TX_PIN, UART_RX_PIN);
    printf("1\n");
    while(uart_is_enabled(UART_ID) == false);

    while(uart_is_readable(UART_ID)) {
        uart_getc(UART_ID);
    }

    getVersion();
    printf("1\n");
    if(getMSG()[0] == ERROR_WRONG_OPCODE_RESPONSE) {
        
        stopReading();
        printf("Module continuouslt reading. Asking it to stop... \n");
        sleep_ms(1500);
    } else {
        

        uart_set_baudrate(UART_ID, BAUD);
        setBaud(baudRate);

        uart_set_baudrate(UART_ID, baudRate);
        sleep_ms(250);
    }
    

    getVersion();
    

    if(getMSG()[0] != ALL_GOOD) {
        return (false);
    }

    setTagProtocol(0x05);
    setAntennaPort();
    return (true);
}

void irq_handler(uint gpio, uint32_t events) {
    if(gpio == MOTION_PIN) { //fix this
        scanning = true;
        startTime = to_ms_since_boot(get_absolute_time());
    }
   
}

void scanning_task(){
    if(scanning) {

    }
    while(scanning) {

        if (to_ms_since_boot(get_absolute_time) - startTime < scanTime) {

        } else {
            //enable motion irq
            scanning = false; 
        }
    }
}

void init_task() {

}



int main () {

    //init gpio
    //init servo
    //init rfid
    //init irq
    //init scanning task
    // loop

    return 0;
}
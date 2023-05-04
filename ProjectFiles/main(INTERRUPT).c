#include "FreeRTOS.h"
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "m6e_uhf_api.h"
#include "servo_api.h"

#define INIT_BAUD 115200
#define FINAL_BAUD 38400
#define READ_POWER 2000

#define UART_ID uart1
#define SERVO_PIN 0
#define MOTION_PIN 28
#define M6E_TX 4
#define M6E_RX 5


#define EPC_LEN 12

boolean scanning = false;
uint32_t scanTime = 15000; //Unit is [ms] and is the length the M6E will scan for
uint32_t startTime;
int validEPC[12] = {0xe2, 0x00, 0x42, 0x00, 0x89, 0x50, 0x60, 0x17, 0x06, 0x8e, 0x05, 0x9d};



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
        //disable Motion IRQ
        printf("Starting to read\n");
        startReading();
    }
    while(scanning) {

        if ((to_ms_since_boot(get_absolute_time) - startTime < scanTime)) {
            
            bool valid_EPC = true; 
    
            if(check() == true) {
                uint8_t responseType = parseResponse();
                if(responseType = )
            }
        } else {
            //enable motion irq
            scanning = false; 
        }
    }
}

//baudRate -> RFID READER
//startPos -> starting angle of servo
void init(long baudRate, int startPos) {
    stdio_init_all();
    sleep_ms(500);
    servoInit(servoPin, startPos);
    sleep_ms(500);
    if(setupNano(FINAL_BAUD) == false) {
        printf("Module failed in initialization: No Response");
    }

    setRegion(REGION_NORTHAMERICA);
    setReadPower(READ_POWER);
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
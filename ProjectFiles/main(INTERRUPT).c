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
#define BUTTON_PIN 22
#define M6E_TX 4
#define M6E_RX 5


#define EPC_LEN 12

bool scanning = false;
bool open = false;

uint32_t scanTime = 1500; //Unit is [ms] and is the length the M6E will scan for
uint32_t startTime;
uint32_t openTime = 1500; //[ms] temporary until reed switch works
uint64_t t;
int validEPC[12] = {0xe2, 0x00, 0x42, 0x00, 0x89, 0x50, 0x60, 0x17, 0x06, 0x8e, 0x05, 0x9d};



bool setupNano(long baudRate) {
    
    sleep_ms(1000);
    uart_init(UART_ID, baudRate);
    gpio_set_function(M6E_TX, GPIO_FUNC_UART);
    gpio_set_function(M6E_RX, GPIO_FUNC_UART);
    sleep_ms(3500);
    begin(UART_ID, M6E_TX, M6E_RX);
    printf("1\n");
    while(uart_is_enabled(UART_ID) == false);

    while(uart_is_readable(UART_ID)) {
        uart_getc(UART_ID);
    }

    getVersion();
    printf("1\n");
    if(getMSG()[0] == ERROR_WRONG_OPCODE_RESPONSE) {
        printf("Module continuously reading. Asking it to stop... \n");
        stopReading();
        sleep_ms(1500);
    } else {
        

        uart_set_baudrate(UART_ID, INIT_BAUD);
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
    printf("a\n");
    scanning = true;
    open = false;
    startTime = to_ms_since_boot(get_absolute_time());
    
}

void scanning_task(){
    //startTime = to_ms_since_boot(get_absolute_time());

    if(scanning) {
        //disable Motion IRQ
        gpio_set_irq_enabled_with_callback(22,GPIO_IRQ_EDGE_RISE, false, &irq_handler);
        printf("Starting to read\n");
        startReading();
    } else {
        printf("not scanning\n");
    }

    while(scanning) {
        
        if ((to_ms_since_boot(get_absolute_time()) - startTime < scanTime)) {
            
            bool valid_EPC = true; 
    
            if(check() == true) {
                uint8_t responseType = parseResponse();
                printf("%d\n", responseType);
                if(responseType == RESPONSE_IS_KEEPALIVE) {
                    printf("scanning \n");
                } else if (responseType == RESPONSE_IS_TAGFOUND) {
                    printf("read success\n");
                    int rssi = getTagRSSI();
                    long freq = getTagFreq();
                    long timeStamp = getTagTimestamp();
                    uint8_t tagEPCBytes = getTagEPCBytes();
                    for(uint8_t i = 0; i < EPC_LEN; i++) {
                        if(validEPC[i] != getMSG()[31+i] ) {
                            printf("%X, ", getMSG()[31 +i]);
                            valid_EPC = false;
                        }
                        printf("\n");
                    }
                    if(valid_EPC == true) {
                        printf("valid tag\n");
                        startTime = to_ms_since_boot(get_absolute_time());
                        scanning = false; //valid tag has been found time to open
                        open = true;
                        
                    }
                }
            }
        } else { //No valid tag found and timeout happened
            printf("time out\n");
            //enable motion irq
            gpio_set_irq_enabled_with_callback(22,GPIO_IRQ_EDGE_RISE, true, &irq_handler);

            scanning = false; 
            open = false;
            //stopReading();
            sleep_ms(500);
        }
    }
    
    if (open == true && scanning == false) { //time to open door
        servoSetPos(SERVO_PIN, 10);
        sleep_ms(1000);
        while((to_ms_since_boot(get_absolute_time()) - startTime < openTime)) {//implement reed switch stuff here

        }
        servoSetPos(SERVO_PIN,85);
        scanning = true;
        open = false; 
    }



    
}

//baudRate -> RFID READER
//startPos -> starting angle of servo
void init(long baudRate, int startPos) {

    //Setting up Servo
    stdio_init_all();
    sleep_ms(500);
    servoInit(SERVO_PIN, startPos);

    //setting up interrupt 
    gpio_set_function(BUTTON_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(BUTTON_PIN,false);
    gpio_pull_down(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(22,GPIO_IRQ_EDGE_RISE, true, &irq_handler);
    sleep_ms(500);

    //setting up RFID Reader
    if(setupNano(FINAL_BAUD) == true) {
        setRegion(REGION_NORTHAMERICA);
        setReadPower(READ_POWER);
    } else {
        printf("Module failed in initialization: No Response");

    }
    



}



int main () {
    // stdio_init_all();
    // gpio_set_function(BUTTON_PIN, GPIO_FUNC_SIO);
    // gpio_set_dir(22,false);
    // gpio_pull_down(22);
    // gpio_set_irq_enabled_with_callback(22,GPIO_IRQ_EDGE_RISE, true, &irq_handler);

    //init scanning task
    init(FINAL_BAUD, 85);
    // scanning = true;
    // open = true;
    xTaskCreate(scanning_task, "RFID Scan Routine", 256, NULL, 1, NULL);
    vTaskStartScheduler();
    // loop
    while(1){
        //printf("Doing Someting\n");
    };
    return 0;
}
#include<stdio.h>
#include "M6E/m6e_uhf_api.h"
#include "pico/stdlib.h"
#include"SERVO/servo_api.h"

#define BAUD 115200
#define UART_TX_PIN 4
#define UART_RX_PIN 5
#define UART_ID uart1
#define SERVO_PIN 0

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
        printf("1.5\n");
        stopReading();
        printf("Module continuouslt reading. Asking it to stop... \n");
        sleep_ms(1500);
    } else {
        printf("2\n");

        uart_set_baudrate(UART_ID, BAUD);
        setBaud(baudRate);

        uart_set_baudrate(UART_ID, baudRate);
        sleep_ms(250);
    }
    printf("3\n");

    getVersion();
    printf("4\n");

    if(getMSG()[0] != ALL_GOOD) {
        return (false);
    }

    setTagProtocol(0x05);
    setAntennaPort();
    return (true);
}


int main() {
    stdio_init_all();
    sleep_ms(3500);
    servoInit(SERVO_PIN, 90);
    sleep_ms(3500);
    int validEPC[12] = {0xe2, 0x00, 0x42, 0x00, 0x89, 0x50, 0x60, 0x17, 0x06, 0x8e, 0x05, 0x9d};
    int lenEPC = 12;
    
    // while(1) {
    //     

    //     char* mes = "hello world";
    //     uart_write_blocking(uart1, mes, 11);
    // }
    if(setupNano(38400) == false) {
        printf("Module failed to respond. please check wiring or code dummy\n");
        while(1);
    }

    setRegion(REGION_NORTHAMERICA);
    setReadPower(500);//5.00 dbm can go higher with more current but this is close to USB max. Device max is 27 dbm
    printf("Starting to read\n");
    startReading();
    // printf("Press a key to begin scanning for tags: \n");
    // char c;
    // while(c = getchar() != '\n' && c != EOF) {
    //     printf("%c\n",c);
    // }
    
    while(1) {
        bool valid_EPC = true;
        if(check() == true) {
            uint8_t responseType = parseResponse();
            if(responseType == RESPONSE_IS_KEEPALIVE) {
                printf("Scanning\n");

            } else if(responseType == RESPONSE_IS_TAGFOUND) {
                int rssi = getTagRSSI();
                long freq = getTagFreq();
                long timeStamp = getTagTimestamp();
                uint8_t tagEPCBytes = getTagEPCBytes();

                printf("rssi[%d", rssi);
                printf("]");
                printf(" freq[%d", freq);
                printf("]");
                printf(" epc[");
                for (uint8_t x = 0; x < tagEPCBytes; x++) {
                    if(getMSG()[31+x] < 0x10) {
                        printf("0");
                    }
                    printf("%x ", getMSG()[31+x]);
                }
                printf("]\n");

                for(uint8_t i = 0; i < lenEPC; i++) {
                    if(validEPC[i] != getMSG()[31+i] ) {
                        valid_EPC = false;
                    }
                }                
                if (valid_EPC == true) {
                    servoSetPos(SERVO_PIN, 20);
                    sleep_ms(5000);
                    servoSetPos(SERVO_PIN, 80);
                }           
            } else if(responseType == ERROR_CORRUPT_RESPONSE) {
                printf("Bad CRC\n");
            } else {
                printf("Unkown Error\n");
            }
           
        }
    }

    return 0;
    

    
}


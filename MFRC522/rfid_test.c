#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "rfid_api.c"


int main() {

    stdio_init_all();
    
    for(int i = 0; i < 50; i++) {
        printf("Start\n");
        sleep_ms(100);
    }

    MFRC_init();

    MFRC_rd_reg(CommandReg);

    MFRC_wr_reg(FIFODataReg, 0x06);
    MFRC_wr_reg(FIFODataReg, 0x07);
    MFRC_rd_reg(FIFOLevelReg);
    MFRC_rd_reg(FIFODataReg);
    MFRC_wr_reg(FIFODataReg, 0x08);
    MFRC_rd_reg(FIFOLevelReg);
    MFRC_rd_reg(FIFODataReg);
    // printf("*****************************\n");
    // printf("MFRC522 Self Test\n");
    // printf("*****************************\n");
    // MFRC_dump_ver();
    // printf("-----------------------------\n");

    // bool result = MFRC_self_test();
    // if(result) {
    //     printf("All Good\n");

    // } else {
    //     printf("Not Good\n");
    // }
    // while(true);
    return 0;
}

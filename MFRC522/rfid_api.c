#include <stdio.h>
#include <string.h>
#include "rfid_api.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"


#define RD_DELAY 10
#define WR_DELAY 10
#define RST_DELAY 10

#define SPI_PORT spi0

#define PIN_CS 2
#define PIN_SCK 6
#define PIN_MISO 4
#define PIN_MOSI 7
#define PIN_RST  22

bool hardReset = false; // indicates if a hard reset has happened previously


//Enables Chip Select for MFRC522 RFID Reader
void cs_select () {
    gpio_put(PIN_CS, 0);
}

//Disables Chip Select for MFRC522 RFID Reader
void cs_deselect () {
    gpio_put(PIN_CS, 1);
}

//Initializes Chip Select pin (Is called in MFRC_INIT function)
void cs_init () {

    gpio_init(PIN_CS);
    sleep_ms(2);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);            // setting NSS (CS) high to initialize since its active low
}

void rst_init() {
    gpio_init(PIN_RST);
    sleep_ms(RST_DELAY);
    gpio_set_dir(PIN_RST, GPIO_OUT);
    gpio_put(PIN_RST, 0);
    sleep_ms(RST_DELAY);
    gpio_put(PIN_RST, 1);
    sleep_ms(50);
    hardReset = true;
}


void MFRC_init() {
    stdio_init_all();
    spi_init(SPI_PORT, MFRC522_BIT_RATE); 

    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    bi_decl(bi_3pins_with_func(PIN_MOSI, PIN_MOSI, PIN_SCK, GPIO_FUNC_SPI));

    cs_init();
    bi_decl(bi_1pin_with_name(PIN_CS, "SPI CS"));

    rst_init();

    if(!hardReset) { //trigger a soft reset if a hard reset has not taken place (it should)
        MFRC_reset();
    }

    // MFRC_wr_reg(TxModeReg, 0x00);
    // MFRC_wr_reg(RxModeReg, 0x00);
    // MFRC_wr_reg(ModWidthReg, 0x26);

    // MFRC_wr_reg(TModeReg, 0x80);
    // MFRC_wr_reg(TPrescalerReg, 0xA9);
    // MFRC_wr_reg(TReloadRegL, 0xE8);
    // MFRC_wr_reg(TReloadRegH, 0x03);

    // MFRC_wr_reg(TxASKReg, 0x40);
    // MFRC_wr_reg(ModeReg, 0x3D);

    MFRC_wr_reg(TModeReg, 0x8D);
    MFRC_wr_reg(TPrescalerReg, 0x3E);
    MFRC_wr_reg(TReloadRegL, 30);
    MFRC_wr_reg(TReloadRegH, 0x00);

    MFRC_wr_reg(TxASKReg, 0x40);
    MFRC_wr_reg(ModeReg, 0x3D);

    MFRC_antennaOn();
    
}

void MFRC_antennaOn() {
    uint8_t value = MFRC_rd_reg(TxControlReg);
    if ((value & 0x03) != 0x03) {
        MFRC_wr_reg(TxControlReg, value | 0x03);
        printf("Antenna Enabled\n");
    }
}


void MFRC_wr_reg(uint8_t reg, uint8_t value) {
    if(spi_is_writable(SPI_PORT) && !spi_is_busy(SPI_PORT)) {
        uint8_t data[2];
        data[0] =  (0xFF & (reg << 1) &  0x7E);
        data[1] = value;
        cs_select();
        spi_write_blocking(SPI_PORT, data, 2); //2 -> length of data array
        cs_deselect();
        sleep_ms(WR_DELAY);

    } else {
        printf("SPI not writable or busy\n");
    }
}

void MFRC_wr_Nreg(uint8_t reg, uint8_t len, uint8_t *values) {
    if(spi_is_writable(SPI_PORT) && !spi_is_busy(SPI_PORT)) {
        cs_select();

        uint8_t data[len + 1];
        data[0] = (0xFF & (reg << 1) &  0x7E); //clear MSB and LSB
        for (int i = 0; i < len; i++) {
            data[i+1] = values[i];
        }

        spi_write_blocking(SPI_PORT, data, len);
        sleep_ms(WR_DELAY);
        cs_deselect();
    } else {
        printf("SPI not writable or busy\n");
    }
}

uint8_t MFRC_rd_reg(uint8_t reg) {
    uint8_t value;
    cs_select();
    
    reg = ((0xFF & (reg << 1) &  0x7E) | 0x80) ;
    printf("Register to read: %b\n", reg);
    spi_write_blocking(SPI_PORT, &reg, 1);

    if(spi_is_readable(SPI_PORT)) {
        printf("Readable\n");
    } else if(spi_is_busy(SPI_PORT)) {
        printf("Port is busy, cant read\n");
    } else if(!spi_is_readable(SPI_PORT)) {
        printf("Not readable\n");
    }
    

    spi_read_blocking(SPI_PORT, 0, &value, 1);
    sleep_ms(RD_DELAY);
    cs_deselect();
    printf("%d\n", value);
    return value;

    // if(spi_is_readable(SPI_PORT) && !spi_is_busy(SPI_PORT)) {
        
    //     reg = reg|0x80;
    //     spi_write_blocking(SPI_PORT, &reg, 1);
    //     sleep_ms(RD_DELAY);
    //     spi_read_blocking(SPI_PORT, 0, &value, 1);
    //     sleep_ms(RD_DELAY);
    //     cs_deselect();
    //     return value;
    // } else {
    //     cs_deselect();
    //     printf("SPI not readable or busy\n");
    // }
}

void MFRC_rd_Nreg(uint8_t reg, uint8_t len, uint8_t *buf) {
    //check if rfid is readable
    cs_select();
    if(spi_is_readable(SPI_PORT) && !spi_is_busy(SPI_PORT)) {
    reg = (reg << 1) | 0x80;
    spi_write_blocking(SPI_PORT, &reg, 1);
    sleep_ms(RD_DELAY);                               //timing subject to change
    spi_read_blocking(SPI_PORT, 0, buf, len); 
    cs_deselect();
    sleep_ms(RD_DELAY);
    } else {
        
        printf("SPI multiple bytes are not readable or busy\n");
    }
    cs_deselect();
}

void MFRC_reset() {
    MFRC_wr_reg(CommandReg, PCD_SoftReset);

    uint8_t count = 0;
    do {
        sleep_ms(50);
    } while ((MFRC_rd_reg(CommandReg) & (1 << 4)) && (++count) < 3);
}

void MFRC_clear_buffer(){
    uint8_t zeros[25] = {0x00};
    MFRC_wr_reg(FIFOLevelReg, 0x80);
    MFRC_wr_Nreg(FIFODataReg, 25, zeros);
    MFRC_wr_reg(CommandReg, PCD_Mem);
}

bool MFRC_self_test() {
    MFRC_reset();

    MFRC_clear_buffer();

    MFRC_wr_reg(AutoTestReg, 0x09);

    MFRC_wr_reg(FIFODataReg, 0x00);

    MFRC_wr_reg(CommandReg, PCD_CalcCRC);

    printf("Self Test Initiated\n");

    uint8_t n;
    for (uint8_t i = 0; i < 0xFF; i++) {
        n = MFRC_rd_reg(FIFOLevelReg);
        if (n >= 64) {
            break;
        }
    }
    MFRC_wr_reg(CommandReg, PCD_Idle);

    uint8_t result[64];

    MFRC_rd_Nreg(FIFODataReg, 64, result);

    MFRC_wr_reg(AutoTestReg, 0x00);

    uint8_t version = MFRC_rd_reg(VersionReg);

    const uint8_t *reference;
    switch (version) {
        case 0x88:	// Fudan Semiconductor FM17522 clone
			reference = FM17522_firmware_reference;
			break;
		case 0x90:	// Version 0.0
			reference = MFRC522_firmware_referenceV0_0;
			break;
		case 0x91:	// Version 1.0
			reference = MFRC522_firmware_referenceV1_0;
			break;
		case 0x92:	// Version 2.0
			reference = MFRC522_firmware_referenceV2_0;
			break;
		default:	// Unknown version
			return false; // abort test
    }

    for (uint8_t i = 0; i < 64; i++) {
        if (result[i] != reference[i]) {
            return false;
        }
    }

    MFRC_init(PIN_MISO, PIN_MOSI, PIN_RST, PIN_CS, PIN_SCK);
    return true;
}


void MFRC_dump_ver() {
    uint8_t version = MFRC_rd_reg(VersionReg);

    printf("Firmware version: %x\n", version);

    switch(version) {
        case 0x88: printf("= (clone)\n"); break;
        case 0x90: printf(" = v0.0\n");     break;
		case 0x91: printf(" = v1.0\n");     break;
		case 0x92: printf(" = v2.0\n");     break;
		case 0x12: printf(" = counterfeit chip\n");     break;
		default:   printf(" = (unknown)\n");
    }

    if ((version == 0x00) || version == 0xFF) {
        printf("Warning: not connected properly\n");
    }
    
}



#include "mbed.h"
#include "ASensor.h"
#include <string.h>
#include <stdbool.h>
/* 
* This File contains answer for the Question1B. 
*
* Reference doc.: Official document for I2C:
*   Website: https://os.mbed.com/docs/mbed-os/v6.15/apis/i2c.html  
*/  


int GetVersion(I2C i2_c){
    // Initalize to store data which will be read afterwards
    char storeData1, storeData2;

    // Initialize the register address according to the datasheet
    // Datasheet: 0x004 - Major Version
    // Datasheet: 0x005 - Minor Version
    char regAddress1[2] = {0x00, 0x04};
    char regAddress2[2] = {0x00, 0x05};

    // Initialze result to store result data 
    int result;
    
    // Write Major Version address to get what store in the register
    i2_c.write(SENSOR_ADDRESS, regAddress1, 2, false);
    ThisThread::sleep_for(500);

    // read one byte from 0x0004 register address
    i2_c.read(SENSOR_ADDRESS, storeData1, 1, false);
    ThisThread::sleep_for(500);

    // Write Minor Version address to get what store in the register
    i2_c.write(SENSOR_ADDRESS, regAddress2, 2, false);
    ThisThread::sleep_for(500);

    // read one byte from 0x0005 register address
    i2_c.read(SENSOR_ADDRESS, storeData2, 1, false);

    // Returns Major Version.Minor Version of the sensor
    result = int((storeData1 << 8) | storeData2);
    return result;
}

int GetTotalStrength(I2C i2_c){

    // Initalize to store data which will be read afterwards
    char storeData1, storeData2;

    // Initialize the register address according to the datasheet
    // Datasheet: 0x01A - Touch strength
    // Datasheet: 0x01B - Touch strength
    char regAddress1[2] = {0x00, 0x1A};
    char regAddress2[2] = {0x00, 0x1B};


    // Initialze result to store result data
    int result;
    
    // Write Touch strength address to get what store in the register
    i2_c.write(SENSOR_ADDRESS, regAddress1, 2, false);
    ThisThread::sleep_for(500);

    // read one byte from 0x001A register address
    i2_c.read(SENSOR_ADDRESS, storeData1, 1, false);
    ThisThread::sleep_for(500);

    // Write Touch strength address to get what store in the register
    i2_c.write(SENSOR_ADDRESS, regAddress2, 2, false);
    ThisThread::sleep_for(500);

    // read one byte from 0x001B register address
    i2_c.read(SENSOR_ADDRESS, storeData2, 1, false);

    // Returns the total strength
    result = int((storeData1 << 8) | storeData2);
    return result;
}

int GetEvent(I2C i2_c){

    // Initalize to store data which will be read afterwards
    char storeData1, storeData2;

    // Initialize the register address according to the question:
    // Check 0x000D – 0x000E register address according to the question
    char regAddress1[2] = {0x00, 0x0D};
    char regAddress2[2] = {0x00, 0x0E};

    // Initialze result to store the judging result
    bool result;

    // Write 0x000D address to get what store in the register
    i2_c.write(SENSOR_ADDRESS, regAddress1, 2, false);
    ThisThread::sleep_for(500);

    // read one byte from 0x000D register address
    i2_c.read(SENSOR_ADDRESS, storeData1, 1, false);
    ThisThread::sleep_for(500);

    // Write 0x000E address to get what store in the register
    i2_c.write(SENSOR_ADDRESS, regAddress2, 2, false);
    ThisThread::sleep_for(500);

    // read one byte from 0x000E register address
    i2_c.read(SENSOR_ADDRESS, storeData2, 1, false);

    /* 
    * Case 1: Returns 0 if there is no event or an enumerated value indicating the event type 
    *         defined by the bits in register addresses 0x000D – 0x000E in the sensor
    */
   result = (storeData1 == 0) && (storeData2 == 0);
    if(result) {
        return 0;
    }

    /* 
    * Case 2: 0x00D Bit 5 == 1. Event type: SWIPE_Y-.
    * RETURN enumerated value 1 to present SWIPE_Y-
    */
    if((storeData1>>5) == 1) {
        return 1;
    }
    /* 
    * Case 3: 0x00D Bit 4 == 1. Event type: SWIPE_Y+.
    * RETURN enumerated value 2 to present SWIPE_Y+
    */
    else if((storeData1>>4) == 1) {
        return 2;
    }
    /* 
    * Case 4: 0x00D Bit 3 == 1. Event type: SWIPE_X+.
    * RETURN enumerated value 3 to present SWIPE_X+
    */
    else if((storeData1>>3) == 1) {
        return 3;
    }
    /* 
    * Case 5: 0x00D Bit 2 == 1. Event type: SWIPE_X-.
    * RETURN enumerated value 4 to present SWIPE_X-
    */
    else if((storeData1>>2) == 1) {
        return 4;
    }
    /* 
    * Case 6: 0x00D Bit 1 == 1. Event type: PRESS_AND_HOLD.
    * RETURN enumerated value 5 to present PRESS_AND_HOLD
    */
    else if((storeData1>>1) == 1) {
        return 5;
    }
    /* 
    * Case 7: 0x00D Bit 0 == 1. Event type: SINGLE_TAP.
    * RETURN enumerated value 6 to present SINGLE_TAP
    */
    else if(storeData1 == 1) {
        return 6;
    }
    /* 
    * Case 8: 0x00E Bit 0 == 1. Event type: 2_FINGER_TAP.
    * RETURN enumerated value 7 to present 2_FINGER_TAP
    */
    else if(storeData2 == 1) {
        return 7;
    }
    /* 
    * Case 9: 0x00E Bit 1 == 1. Event type: SCROLL.
    * RETURN enumerated value 8 to present SCROLL
    */
    else if((storeData2>>1) == 1) {
        return 8;
    }
    /* 
    * Case 10: 0x00E Bit 2 == 1. Event type: ZOOM.
    * RETURN enumerated value 9 to present ZOOM,
    */
    else if((storeData2>>2) == 1) {
        return 9;
    }
    /* 
    * Case 11: NO EVENT.
    */
    else {
        return 0;
    }

}




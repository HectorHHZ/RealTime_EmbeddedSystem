/* 
* This File contains answer for the Question1A. 
*/


// According to the datasheet: I2C: The full slave address byte will thus be 0xE9 (read) or 0xE8 (write).
#define SENSOR_ADDRESS 0xE8

// Define three functions according to QUESTION.
int GetVersion();       
int GetTotalStrength(); 
int GetEvent();
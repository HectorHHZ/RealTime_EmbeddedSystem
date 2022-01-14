#include <mbed.h>
#include <string.h>
#include "ASensor.cpp"

/* 
* This File contains answer for the Question-1C， Question-1D， Question2, and Question3.
*   Reference doc 1.: Official document for PwmOut:
*      Website: https://os.mbed.com/docs/mbed-os/v6.15/mbed-os-api-doxy/classmbed_1_1_pwm_out.html#a04593bbcefdddb53406c0943a711f293
*   Reference doc 2.: Official full document for I2C: There is no need for additional wake up setting for I2C
*      Website: https://www.azoteq.com/images/stories/pdf/iqs5xx-b000_trackpad_datasheet.pdf. ->Page 26, 7.3.1 section, I2C Wake 
*/

// This is a hypothetical implementation.
// Initialize the I2C driver. For question 1C
I2C i2_c(I2C_SDA, I2C_SDL);
// Accorting to Reference doc 2.: Official full document for I2C
// There is no need to additional wake up. The device can be woken from suspend by addressing it on the I2C bus.

// Initialize the ticker for Question 2.
Ticker T;

//Initialize the LED for Question 3.
PwmOut led1(LED1);

// Initialize the flag. 
int flag = 0;

// Function Prototypes
void setFlag();
void wait_ms(uint32_t ms);
void question1D();

/* main function - comment out parts you aren't currently running! */
int main() {
  // Setup a 0.5 second ticker and implement the “attach” for question2.a
  // attach function: Parameter1: func – pointer to the function to be called. Parameter 2: t – the time between calls in seconds
  T.attach(&setFlag, 0.5);

  // Set the PWM frequency to 1kHz.
  led1.period_ms(1);

  while(1) {

    // For Question-1D. Comment other implementations when you run question 1D.
    // Also, comment 1D when you run others
    question1D();

    // For Question-2.b
    if (flag != 0) {
      int newEvent = GetEvent(i2_c);
      flag = 0;
      printf("%d\n\r", newEvent);
    }

    // For Question-3. We define the threshold to 30000. The largest number is 65535(Largest number in 16 bits)
    // When the strength cross the threshold -> BRIGHT with high power 
    // When the strength under the threshold -> DIM 
    int newStrength = GetTotalStrength();
    float brightness = (float) newStrength / 65355;
    led1.write(brightness);
    // Reference doc 2.: Official document for PwmOut:
    // Website: https://os.mbed.com/docs/mbed-os/v6.15/mbed-os-api-doxy/classmbed_1_1_pwm_out.html#a04593bbcefdddb53406c0943a711f293
    // A floating-point value representing the output duty-cycle, specified as a percentage. 
    // The value should lie between 0.0f (representing on 0%) and 1.0f (representing on 100%). 
    // Values outside this range will be saturated to 0.0f or 1.0f.
  }
}

// Build the wait function
void wait_ms(uint32_t ms) {
  wait_us(1000*ms);
}


// This function will be used in ticker attach for GetEvent function. 
void setFlag(){
  flag = 1;
}

/* For Question-1D
* Call the GetEvent() function every 0.5 second and 
* Outputs the result of the GetEvent function to the serial terminal.
*/
void question1D(){
  int newEvent = GetEvent(i2_c);
  printf("%d\n\r", newEvent);  
  wait_ms(500);
}

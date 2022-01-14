/*
* Project:    Assignment3
* File:       main.cpp
* Author(s):  Michael Thoreau, Chris Piekarski
* Studen Name: Haoze He
* Student ID: hh2537
*/

#include <mbed.h>

//References
// PwmOut https://os.mbed.com/docs/mbed-os/v6.9/apis/pwmout.html
// AnalogIn https://os.mbed.com/docs/mbed-os/v6.15/apis/i-o-apis.html


/*	Signal Graphing
*	In this exercise you must utilize a timer/ticker to monitor the Analog ADC pins and sample their values.
*	Set up PB_0 for PwmOut and set up PB_1 for AnalogIn. Initiate a PWM signal of 1Hz with a 20% duty cycle on PB_0.
*	When sampling, you must short the pins PB_0 and PB_1. One method is to utilize jumper JP2 that comes with your board!
*	For this task, you will sample the ADC for 5 seconds at 500 samples/second. Store your samples in a buffer and then output the buffer to the terminal.
*	From the terminal, record and graph your collected data in either Matlab or Python (Using matplotlib libraries)
*	and submit the resulting graph as a jpg/png as part of this assignment. Remember to label the x & y axis correctly.
* 	you must be able to show that the frequency of the square wave is as expected
*/

// recommended steps:
// create a PWMOut on PB_0
// create a ticker to read from the an AnalogIn on PB_1
// set up a way to write to a buffer in the ticker callback
// output values in the main loop

// Step1: create a PWMOut on PB_0
// Step2: create a ticker to read from the analogIn on PB_1
Ticker simpleMaker;
AnalogIn ain(PB_1);
PwmOut pout(PB_0);

float buffer[2500];
int new_flag = 0;

void set_ADC(){
	new_flag = 1;
}



int main() {

	// Initialize: set period to 1 second.  Set 20% duty cycle, relative to period.
	int counter = 0;
	pout.period(1.0f);     
    pout.write(0.20f);      

	simpleMaker.attach_us(&set_ADC, 2000);
	
	while (1) {
	
		// Step3: write to a buffer in the ticker callback
		if (new_flag == 1) {
			buffer[(counter++)] = ain.read();
			if(counter == 2501) counter = 0;
			new_flag = 0;
		}

		//Step4: Output values in the main loop
		if(counter == 2500){
			printf("data = [");
			for (int i = 0; i < 2500; i++) {
				printf("%d,", (int)(1000 * buffer[i]));
			}
			printf("]\n\r\n\r");
		}
	}
}

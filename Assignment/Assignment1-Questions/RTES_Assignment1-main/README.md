# Real Time Embedded Systems
### Programming Assignment 1 - Introduction

<br />

The purpose of this assignment is to get you comfortable with the development environment as well as the basics of microcontroller programming and debugging. 

All questions should be answered by modifying the main.c file; Add comments and code to the file where required and rename your main.c file as Assignment1_**nyuid**.c  before submitting on NYU classes.

The assignment will be graded according to the following:

| Part        | Grade       |
| ------------| ----------- |
| 1a          | 50%         |
| 1b          | 10%         |
| 1c          | 10%         |
| 2           | 10%         |
| Extension   | 20%         |


### Instructions

Create a new project in platformIO as demonstrated in class. Copy the code from main.c in this repository to your main.c file and modify to complete each part. You also need to copy mbed_app.json from the git repository to the top level of your project (next to platformio.ini) this allows us to print floats!


<br />

---

<br />


**FAQ**

**Old Board: My code gets stuck at:**   `serial = new USBSerial()`

You have to plug in a second usb cable to use the USBSerial interface. See these [Instructions](tutorials/USBSerial.md).


<br />


**Old Board: My code no longer appears to run when connected to an external power source?**

This is caused by a firmware bug in the st-link controller on the board. Follow these [Instructions on Updating the Firmware](tutorials/firmware.md) on your board.

<br />

**Old Board: I'm not seeing any data from printf()?**

Make sure to follow all the instructions [here](tutorials/USBSerial.md).

<br />

**I have another question/issue?**

Contact a the professor or a TA, one place to start: mjt9978@nyu.edu

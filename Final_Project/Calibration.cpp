#include <mbed.h>

/*
DataReading:  -- 20% - Ability to successfully and continuously measure gyro values from the angular velocity sensor
Use SPI, Ticker to read the data.
SPI, TICKER -> setFlag(), setMode();
ReadData -> readData();

Calibration: -- 15% - Creativity
Calibration1: We utilize calibration to eliminate the influence of the fluctuate of the raw data. 
Calibration2: Verify the relationship between angular speed and the raw data from the sensor.
*/

volatile int flag = 0;
SPI spi(PF_9, PF_8, PF_7); // mosi, miso, sclk
DigitalOut cs(PC_1);
int16_t dataSet[4000];
void setFlag();
void setMode();
int16_t readData(int code);
double calibration1();
double calibration2();
int16_t offset;

int main() {
  cs=1;
  setMode();
  spi.format(8,3);
  spi.frequency(100000);
  Ticker t;
  t.attach(&setFlag,0.01);
  uint16_t iter = 0;

  while(1) {
    if(flag){
      int16_t dataZ = readData(0xAC);
      printf("%d\n", iter);
      dataSet[iter] = dataZ;
      iter = iter + 1;

      if (iter == 4000){
          double cal1 = calibration1();
          printf("\nThe first round of calibration gives %d\n", (int)cal1);
          offset=-63;
          double cal2 = calibration2();
          printf("\nThe second round of calibration gives %d\n", (int)cal2);
        break;
      }
      flag = 0;
    }
    
  }
}

void setFlag() {          
  flag = 1;
}

void setMode() {          
  cs=0;
  spi.write(0x20);
  spi.write(0xCF);
  cs=1;
}

/*
- 20% - Ability to successfully and continuously measure gyro values from the angular velocity sensor
*/
int16_t readData(int code){
  cs = 0;
  spi.write(code);
  uint8_t xl = spi.write(0x00);
  cs = 1;
  cs = 0;
  spi.write(code + 1);
  int8_t xh = spi.write(0x00);
  cs = 1;
  int16_t data = xh*256+xl;
  return data;
}

/*
Function: Calibration1
Idea: Elimintate the flucturation of the raw data.
      calculate the average value of raw data without moving the clip
*/
double calibration1(){
  double total = 0;
  for (int i = 0; i < 4000; i++){
    total+=dataSet[i];
    //printf("%d ",dataSet[i]);
  }
  return total/4000;
}

/*
Function Calibration2
Verify the relationship between angular speed and the raw data from the sensor.
According to datasheet, the sensitivity of the gyroscope, when FS = 245 dps and typical values at +25 °C,the transfer factor is 8.75 mdps/digit. (Page 10 of the datasheet). 
*/

double calibration2(){
  double total = 0;
  for (int i = 0; i < 4000; i++){
    total+=(dataSet[i]-offset);
    //printf("%d ",dataSet[i]);
  }
  return total/3600;
}
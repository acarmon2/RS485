#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <LSM303.h>
#include <L3G.h>
#include <SFE_BMP180.h>

#define ALTITUDE 2160.0           // Llanogrande, area near to Rionegro, Antioquia, Colombia

// main objects
LSM303 compass;
L3G gyro;
SFE_BMP180 pressure;
SoftwareSerial portOne(10, 11);

// main vector with values
int16_t Data[10];
char c, status;
double T,P,p0,a;

void setup() {
  // init serial ports, analog and digital
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  portOne.begin(9600);
  // init i2c protocol
  Wire.begin();
  // init setup and default of each module
  compass.init();
  compass.enableDefault();
  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }
  gyro.enableDefault();
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail\n\n");
    while(1);
  }
}

void loop() {
// Silence in serial port
while(!Serial.available()){
  if(c == 'R'){
    compass.read();
    gyro.read();
    Data[0] = (int16_t)compass.a.x;
    Data[1] = (int16_t)compass.a.y;
    Data[2] = (int16_t)compass.a.z;
    Data[3] = (int16_t)compass.m.x;
    Data[4] = (int16_t)compass.m.y;
    Data[5] = (int16_t)compass.m.z;
    Data[6] = (int16_t)gyro.g.x;
    Data[7] = (int16_t)gyro.g.y;
    Data[8] = (int16_t)gyro.g.z;
    for(int i = 0; i < 9; i++){
      Serial.print(Data[i]);
      Serial.print(" ");
    }
    status = pressure.startTemperature();
    if(status != 0){
      delay(status);
      status = pressure.getTemperature(T);
      if(status != 0){
        Serial.print(T);
        Serial.print(" ");
      }
      status = pressure.startPressure(3);
      if(status != 0){
        delay(status);
        status = pressure.getPressure(P,T);
        if(status != 0){
          p0 = pressure.sealevel(P,ALTITUDE);
          a = pressure.altitude(P,p0);
          Serial.print(a);
          Serial.print(" ");
        }
      }
    }
    Serial.println("");
    c = '\0';
    delay(30);
  }
}

// Capture the symbol in serial port
while(Serial.available() > 0){
  if(Serial.available() > 0){
    c =  Serial.read();
  }
}
}

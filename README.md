# RS485
In this system we have a inertial module connected a tracking system (motor + Antenna). Far away (30.0 m) we need to connect the system (That is the reason to use RS485).

The system use Arduino and RS485 shield (v1.0), although the G5500 has a position feedback, we need the horizon and a little bit fast feedback system. In fact, GY-89 has embebed three sensors, the BMP180 allows to measure the temperature and the altitude of the region where the Ground Station stay.

There are two elements named as following: Sensor and Ground. The Sensor has the IMU and it is adapted mechanically to the fixed system of antennas. The another one system (Ground) is an arduino that receive the signals of the sensor using RS485 protocol. 

# The Sensor
For the sensor is very easy to findd the libraries for the three modules (LSM303, L3GD20 and BMP180). The connection with the RS485 shield is standard (Arduino) and for the control select Auto and On (Off is the case where you need to program the Arduino with the shield connected).

# The Ground
For the ground, we need to separate the USB (Serial hardware for Arduino) of the AB signal provide by IC MAX485 (https://datasheets.maximintegrated.com/en/ds/MAX1487-MAX491.pdf) 


#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "math.h"

MPU6050 MPU6050_sensor;
int16_t datax, datay, dataz;
int16_t pitch, roll;
float Gx, Gy, Gz;
unsigned long startTime, endTime, elapsedTime, WCET = 0;

void setup() {
    Serial.begin(38400);
    Wire.begin();
    MPU6050_sensor.initialize();
}

void loop() {
    startTime = micros();
    MPU6050_sensor.getAcceleration(&datax, &datay, &dataz);
    Gx = datax / 16384.0;
    Gy = datay / 16384.0;
    Gz = dataz / 16384.0;
    pitch = atan2(-Gx, sqrt(Gy * Gy + Gz * Gz)) * 180.0 / M_PI;
    roll = atan2(Gy, Gz) * 180.0 / M_PI;
    endTime = micros();
    elapsedTime = endTime - startTime;
    if (elapsedTime > WCET) WCET = elapsedTime;
    Serial.println(WCET);
}

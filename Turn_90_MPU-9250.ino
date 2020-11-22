#include "MPU9250.h"
MPU9250 IMU(Wire,0x68);
int status;

void setup() {
  // serial to display data
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);
}
float sum = 0;
float x = 0;
float angle = 0;
float reading = 0;

void loop() {
  
  while (x < 90.0 && x > -90.0){
    IMU.readSensor();
    reading = IMU.getGyroZ_rads(),6;
    sum = sum + reading;
    angle = sum * 0.2;
    angle = angle * (180/3.14);
    x = x + angle;
    Serial.println(x);


    delay(200);
  }
  Serial.println("Angle reached 90 degrees");
  delay(200);
}
  
  

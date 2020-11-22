#define PWMa 7
#define PWMb 5
#define PWMc 8
#define PWMd 6


// define a limit value
#define LIMIT 1000
#include "MPU9250.h"
MPU9250 IMU(Wire,0x68);
int status;

int trig = 9;
int echo = 10;
float dist, dur, dist1, dur1;
float cm = 15;
int ang;


void setup() {
  // configure the motor control pins as outputs
  pinMode(PWMa, OUTPUT);
  pinMode(PWMb, OUTPUT);
  pinMode(PWMc, OUTPUT);
  pinMode(PWMd, OUTPUT);

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


  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void turn(int ang){
  float sum = 0;
  float x = 0;
  float angle = 0;
  float reading = 0;
  while (x < ang){
    IMU.readSensor();
    reading = IMU.getGyroZ_rads(),6;
    sum = sum + reading;
    angle = sum * 0.2;
    angle = angle * (180/3.141592654);
    x = x + angle;
    delay(100);

}
}





void loop(){

  //drive forward
  digitalWrite(PWMa, LOW);
  digitalWrite(PWMb, HIGH);
  digitalWrite(PWMc, HIGH);
  digitalWrite(PWMd, LOW);
  
  delay(1000);

  
//rotate 180
  digitalWrite(PWMa, HIGH);
  digitalWrite(PWMb, LOW);
  digitalWrite(PWMc, HIGH);
  digitalWrite(PWMd, LOW);
  turn(115);
  digitalWrite(PWMa, LOW);
  digitalWrite(PWMb, LOW);
  digitalWrite(PWMc, LOW);
  digitalWrite(PWMd, LOW);
  delay(300);
  digitalWrite(PWMa, HIGH);
  digitalWrite(PWMb, LOW);
  digitalWrite(PWMc, HIGH);
  digitalWrite(PWMd, LOW);
  turn(115);
  



//reverse to wall
  bool y = true;
  bool z = true;
  while (z == true){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    dur = pulseIn(echo, HIGH);
    dist = (dur/2) / 29.1;
    digitalWrite(PWMa, HIGH);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, HIGH);
    if (dist <= cm){
      z = false;
      digitalWrite(PWMa, LOW);
      digitalWrite(PWMb, LOW);
      digitalWrite(PWMc, LOW);
      digitalWrite(PWMd, LOW);
    }
    delay(100);
  }

  

  delay(100);
//turn 90
  digitalWrite(PWMa, LOW);
  digitalWrite(PWMb, LOW);
  digitalWrite(PWMc, HIGH);
  digitalWrite(PWMd, LOW);
  turn(90);

  
  delay(250);


// reverse to wall
  
  
  while(y == true){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    dur1 = pulseIn(echo, HIGH);
    dist1 = (dur1/2) / 29.1;
    digitalWrite(PWMa, HIGH);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, HIGH);
    if (dist1 <= cm){
      y = false;
      digitalWrite(PWMa, LOW);
      digitalWrite(PWMb, LOW);
      digitalWrite(PWMc, LOW);
      digitalWrite(PWMd, LOW);
    }
    delay(100);
  }


  //stop
  delay(100);
  digitalWrite(PWMa, LOW);
  digitalWrite(PWMb, LOW);
  digitalWrite(PWMc, LOW);
  digitalWrite(PWMd, LOW);

  delay(2000);
  
  
  
  
  
  
}

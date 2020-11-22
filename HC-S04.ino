int trig = 3;
int echo = 2;
float dist, dur;
bool x = true;
void setup(){
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop(){
  while (x == true){
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  dur = pulseIn(echo, HIGH);
  dist = (dur/2) / 29.1;
  Serial.print("\nDistance (cm):\n");
  Serial.print(dist);
  if (dist <= 10){
    Serial.print("Less than 10");
    x = false;
  }
  delay(500);
  
  }
}

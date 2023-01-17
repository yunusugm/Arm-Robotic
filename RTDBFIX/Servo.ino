void setupServo() {
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  shoulder.setPeriodHertz(50);
  elbow.setPeriodHertz(50);
  base.setPeriodHertz(50);
  wrist.setPeriodHertz(50);
  grip.setPeriodHertz(50);

  base.attach(basePin, 500, 2400);  
  shoulder.attach(shoulderPin, 500, 2400);  
  elbow.attach(elbowPin, 500, 2400);     
  wrist.attach(wristPin, 500, 2400); //D6
  grip.attach(gripPin, 500, 2400); //D7

  base.write(0);
  shoulder.write(0);
  elbow.write(0);
  wrist.write(0);
  grip.write(0);
  Serial.println("Done servo set");
}

void resetTask() {
  shoulder.write(0);
  delay(2000);
  elbow.write(120);
  delay(2000);
  base.write(90);
  delay(2000);
  wrist.write(46);
  delay(2000);
  grip.write(10);
  delay(2000);
  Serial.println("Done reset");
}

void firstTask() {
  shoulder.write(0);
  delay(2500);
  grip.write(35);
  delay(2500);
  elbow.write(35);
  delay(2500);
  base.write(0);
  delay(2500);
  elbow.write(120);
  delay(2500);
  wrist.write(20);
  delay(2500);
  grip.write(0);
  delay(2500);
  elbow.write(30);
  delay(2500);
  base.write(90);
  delay(2500);
  elbow.write(120);
  delay(2500);
  grip.write(35);
  delay(2500);
  Serial.println("Done task 1");
}
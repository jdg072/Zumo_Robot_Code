String speedStr;
String turnStr;
char speedSign;
char turnSign;
L3G  gyro;
int32_t angle = 0;
int absValueAngle;
int absValueTurnInt;
int speedInt = 0;
int turnInt = 0;

int32_t getAngle(){
  //turnAngle is a variable defined in TurnSensor.cpp
  //This math converts the number into degrees since the last 
  //sensor reset
  return(((int32_t)turnAngle >> 16) * 360) >> 16;
}

void readSpeedSign(){
  char c = Serial1.read();

  if(c == '+' || c == '-'){
    speedSign = c;
    delay(10);
    //Serial.print("speed Sign: ");
    //Serial.println(speedSign);
  }
  else{
    ProtocolChar = c;
  }
}

void readSpeedStr(){
  while(Serial1.available()){
    delay(10);

    char c = Serial1.read();
    if (c =='#'){
      break;
    }
    speedStr += c;
    //Serial.print("Speed String");
    //Serial.println(speedStr);
  }
}

void readTurnSign(){
  turnSign = Serial1.read();
  delay(10);
}

void readTurnStr(){
  while(Serial1.available()){
    delay(10);

    char c = Serial1.read();
    if(c == '#'){
      break;
    }
    turnStr += c;
    //Serial.print("Turn String: ");
    //Serial.println(turnStr);
  }
}

void intoInt(){
  speedInt = speedStr.toInt();
  turnInt = turnStr.toInt();

  if(speedSign == '-'){
    speedInt = speedInt*(-1);
  }

  if(turnSign =='-'){
    turnInt = turnInt*(-1);
  }
  
}

void turnRobot(){
  if(turnInt < 0){
    motors.setLeftSpeed(175);
    motors.setRightSpeed(-175);
  }
  else{
    motors.setLeftSpeed(-175);
    motors.setRightSpeed(175);
  }
  turnSensorUpdate();
  angle = getAngle();
  absValueAngle = abs(angle);
  absValueTurnInt = abs(turnInt);
  
  while(absValueAngle < absValueTurnInt){ 
    delay(5);
    turnSensorUpdate();
    angle = getAngle();
    absValueAngle = abs(angle);
    absValueTurnInt = abs(turnInt);
    Serial.println(angle);
  }
  motors.setRightSpeed(0);
  motors.setLeftSpeed(0);
}

void readStr(){
  readSpeedSign();
  readSpeedStr();
  readTurnSign();
  readTurnStr();
  intoInt();
  speedStr = "";
  turnStr = "";
  turnSign = "";
  speedSign = "";
}

void driveMotors(int a){
  motors.setLeftSpeed(a);
  motors.setRightSpeed(a);
  //delay(DELAY);
}

void autonomous_mode(){
  Serial.println("In Language loop");
  while(ProtocolChar != ';'){
  
    if(Serial1.available()){
      readStr();
      driveMotors(0);
      if(turnInt != 0){
        turnRobot();
        turnSensorReset();
        delay(100);
      }
      if(speedInt != 0){
        driveMotors(speedInt);
      }
    }
  }
  //Serial.println("Exiting Basic Language Loop");
}

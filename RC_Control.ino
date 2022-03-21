#include <Wire.h>
#include <Zumo32U4.h>

//Zumo32U4Motors motors;
//Zumo32U4ButtonA buttonA;

char RC_COMMAND;

void stopMotors(){
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

void forwardMotors(){
  motors.setLeftSpeed(200);
  motors.setRightSpeed(200);
  //delay(DELAY);
}

void backwardMotors(){
  motors.setLeftSpeed(-200);
  motors.setRightSpeed(-200);
  //delay(DELAY);
}

void turnLeft(){
  motors.setLeftSpeed(-100);
  motors.setRightSpeed(100);
  //delay(DELAY);
 
}

void turnRight(){
  motors.setLeftSpeed(100);
  motors.setRightSpeed(-100);
  //delay(DELAY);
}

/*In RC Mode once a command has been sent (forward, backward, left, right)
 * the robot will continue that action until the stop signal is sent
 * 
 */
void RC_MODE(){ 
  Serial.println("In RC Mode");
  while(ProtocolChar != ';'){  //Will stay in RC Mode activity until instructed to leave by phone
    if(Serial1.available()){ 
      RC_COMMAND = Serial1.read(); //Read the data and enter the controls
      if(RC_COMMAND == ';'){
        ProtocolChar = RC_COMMAND;
        break;
      }
      driveControls(RC_COMMAND);
    }
  }
  Serial.println("exiting RC Mode");
}

void driveControls(char key) {
   switch (key){
      case 49:
        forwardMotors();
        //num = 48;
        break;
      case 50:
        backwardMotors();
        //num = 48;
        break;
      case 51:
        turnRight();
        //num = 48;
        break;
      case 52:
        turnLeft();
        //num = 48;
        break;
      default:
        stopMotors();
        
  }
}

#include <CapacitiveSensor.h>
#include <Servo.h>

#define IN 2 //GPIO 2 But Pin 4
#define OUT 4//GPIO 4 But Pin 2
 
CapacitiveSensor cs_4_2 = CapacitiveSensor(IN, OUT);

/* 
  state 0 = serial control of all 3 servos
  state 1 =  session
  state 3 = random session
*/
byte state = 1;

Servo servo1;
Servo servo2;
Servo servo3;


int pos = 0;
int oldPos = 0;
int startPos = 0;
int endPos = 180;
int servoSpeed = 2;
bool servosDetached;
int parsedValue = 0;

int capThreshold = 4000;


void setup(){
  Serial.begin(9600);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  servo1.attach(14); //GPIO 14 But D5
  servo2.attach(12); //GPIO 12 But D6
  servo3.attach(13); //GPIO 13 But D7
  servo1.write(startPos); 
  servo2.write(startPos); 
  servo3.write(startPos);
  servosDetached = false;
}

void loop(){
  long total1;

  switch(state){
    case 0:
      if(Serial.available() > 0){
        parsedValue = Serial.parseInt();
        parsedValue = constrain(parsedValue, 0,180);
      
        if(parsedValue > startPos && oldPos >= pos){
         for(pos = oldPos; pos < parsedValue; pos += servoSpeed){
            servo1.write(pos); 
            servo2.write(pos); 
            servo3.write(pos); 
            delay(15);
            oldPos = pos;
          }
        }else if(parsedValue > startPos && oldPos <= pos){
          for(pos = oldPos; pos > parsedValue; pos -= servoSpeed){
            servo1.write(pos); 
            servo2.write(pos); 
            servo3.write(pos); 
            delay(15);
            oldPos = pos;
          }
        } 
      }    
    break; 

    case 1: 
      total1 = cs_4_2.capacitiveSensor(30);
      
      Serial.println(total1);
      if (Serial.available() > 0 && total1 > capThreshold){
      Serial.println("Cap Button Pressed");
        if (servosDetached == true){
          servo1.attach(14); //GPIO 14 But D5
          servo2.attach(12); //GPIO 12 But D6
          servo3.attach(13); //GPIO 13 But D7
          servosDetached = false;
        }
        //servoSession(2000,500);
        sweepAll();
      }else{
       /* servo1.detach();
        servo2.detach();
        servo3.detach();
        servosDetached = true;*/
      }
    break;
    default:
      servo1.write(0);
      servo2.write(0);
      servo3.write(0);
  }
}
        
  
  /*for(pos = 0; pos <= 180; pos +=1){
    servo1.write(pos);
    delay(15);
  }
  for(pos = 180; pos >= 0; pos -=1){
      servo1.write(pos);
      delay(15);
  }
*/


//Function to sweep a Servo from Start to Endposition and Back
void sweepServo(Servo s){
  for (pos = startPos; pos <= endPos; pos += servoSpeed){
    s.write(pos);
    delay(15);
  }
  for (pos = endPos; pos >= startPos; pos -= servoSpeed){
    s.write(pos);
    delay(15);
  }
}

void sweepAll(){
  sweepServo(servo1);
  sweepServo(servo2);
  sweepServo(servo3);
  delay(2000);
}

void servoSession(int longPause, int shortPause){
  Serial.println("Servosession reached");
  sweepServo(servo1);
  //delay(longPause);
  sweepServo(servo1);
  delay(shortPause);
  sweepServo(servo2);
  delay(longPause);
  sweepServo(servo2);
  delay(shortPause);
  sweepServo(servo3);
  delay(longPause);
  sweepServo(servo3);
}


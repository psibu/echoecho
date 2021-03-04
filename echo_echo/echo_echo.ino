#include <CapacitiveSensor.h>
#include <Servo.h>

/*class myServo{
  Servo servo;
  int pos;
  int startPos = 0;
  int endPos;
  int updateInterval;
  int delay;
  int servoSpeed; 
  bool movingForward;
  unsigned long lastUpdate;
 
  public:
    myServo(int interval){
      updateInterval = interval;
      servoSpeed = 5;
    }
    //constructor to sweep in a correct delay
    myServo(int _delay, int _updateInterval, int _servoSpeed){
      updateInterval = _updateInterval;
      delay = _delay;
      servoSpeed = _servoSpeed;
    }
    void Attach(int pin){
      servo.attach(pin);
      servo.write(startPos);
    }
    void Detatch(){
      servo.detach();
    }
    void Update(){
      if(millis() - lastUpdate + delay > delay){
       // lastUpdate = millis();
        pos += servoSpeed;
        servo.write(pos);
        //Serial.prin
        if((pos >= endPos && pos <= startPos && millis() - lastUpdate + delay > delay) ){
          lastUpdate = millis();
          pos -= servoSpeed; 
        }
      }
    }
};
*/

#define IN 2 //GPIO 2 But Pin 4
#define OUT 4//GPIO 4 But Pin 2
 
CapacitiveSensor cs_4_2 = CapacitiveSensor(IN, OUT);

/* 
  state 0 = serial control of all 3 servos
  state 1 =  session // initial
  state 2 = all together 
  state 3 = random session
*/
byte state = 1;
int parsedValue = 0;

Servo servo1;
Servo servo2;
Servo servo3;

int capThreshold = 40000;
int servoDelay = 1500;
int longPause = 4000;
int shortPause = 1000;
int waitfactor = 10;


int pos = 0;
int oldPos = 0;
int startPos = 90;
int endPos = 120;

int servoSpeed = 1;
int updateInterval = 10;
bool servosDetached;
bool movingForward = false;

bool capPressed = false;

String description = "text";
String combi = "";

//unsigned long previousMillis = 0;
//long interval = 1000;
long period = 2000;
unsigned long time_now = 0;

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
  time_now = millis();
  long total1;

  switch(state){
    ////////////////////////////////////////////  CASE 0 SERIAL CONTROL   //////////////////////////////////////////////////////////////
    case 0:
      if(Serial.available() > 0){
        parsedValue = Serial.parseInt();
        parsedValue = constrain(parsedValue, 0,180);
      
        if(parsedValue > startPos && oldPos >= pos){
         for(pos = oldPos; pos < parsedValue; pos += servoSpeed){
            servo1.write(pos); 
            servo2.write(pos); 
            servo3.write(pos); 
            delay(updateInterval);
            oldPos = pos;
          }
        }else if(parsedValue > startPos && oldPos <= pos){
          for(pos = oldPos; pos > parsedValue; pos -= servoSpeed){
            servo1.write(pos); 
            servo2.write(pos); 
            servo3.write(pos); 
            delay(updateInterval);
            oldPos = pos;
          }
        } 
      }    
    break; 

    ////////////////////////////////////////////  CASE 1 Button & SESSION   //////////////////////////////////////////////////////////////
    case 1: 
      
      total1 = cs_4_2.capacitiveSensor(30);
      description = "Cap val: ";
      combi = description + total1;
      Serial.println(combi);
      
      if (total1 > capThreshold){
        capPressed = true;
        Serial.println("Cap Button Pressed");
        state = 3;
      }

      

    break;

    case 3:
      if(capPressed == true){
        servoSession();
        state = 1;
        if(millis() - time_now > period){
          time_now = millis();
          Serial.println("////////////////////////////////////////////");
          //capPressed = false; 
        }
      }

    break;

    ////////////////////////////////////////////  CASE 2 Button & ALL   //////////////////////////////////////////////////////////////
    case 2:
    total1 = cs_4_2.capacitiveSensor(30);
    description = "Cap val: ";
    combi = description + total1;
    Serial.println(combi);
    
    if (total1 > capThreshold && capPressed == false){
        capPressed = true;
        Serial.println("Cap Button Pressed");
      }

    if(capPressed == true){
      //sweepAll();
      
      capPressed = false;
      }
    break;
    ////////////////////////////////////////////  DEFAULT  //////////////////////////////////////////////////////////////
    default:
      servo1.write(startPos);
      servo2.write(startPos);
      servo3.write(startPos);
  }
}

//Sweep Servo
void sweepServo(Servo s){
  for (pos = startPos; pos <= endPos; pos += servoSpeed){
    s.write(pos);
    delay(updateInterval);
  }
  for (pos = endPos; pos >= startPos; pos -= servoSpeed){
    s.write(pos);
    delay(updateInterval);
  }
}
//Back or forth one direction (no sweep)
void pressButton(Servo s){
  if(!movingForward){
    for (pos = startPos; pos <= endPos; pos += servoSpeed){
      s.write(pos);
      delay(updateInterval);
      
    }
  }else if(movingForward){
    for (pos = endPos; pos >= startPos; pos -= servoSpeed){
    s.write(pos);
    delay(updateInterval);
    } 
  }
}

//SESSION BAF 
void servoSession(){
  pressButton(servo1);
  delay(servoDelay);
  pressButton(servo2);
  delay(servoDelay);
  pressButton(servo3);
  delay(servoDelay);
  movingForward = !movingForward;  
  capPressed = false;
 /* delay(servoDelay * waitfactor);
  pressButton(servo3);
  delay(servoDelay);
  pressButton(servo2);
  delay(servoDelay);
  pressButton(servo1);
  delay(servoDelay);*/
  //movingForward = !movingForward;  
}

void pressMultiButtons(){
  if(!movingForward){
    for (pos = startPos; pos <= endPos; pos += servoSpeed){
        servo1.write(pos);
        servo2.write(pos);
        servo3.write(pos);
        delay(updateInterval);
    }
  }else if(movingForward){
    for (pos = endPos; pos >= startPos; pos -= servoSpeed){
      servo1.write(pos);
      servo2.write(pos);
      servo3.write(pos);
      delay(updateInterval);
    }
  }
}

/*void sweepAll(int longPause){
  pressMultiButtons();
  movingForward = !movingForward;
}*/

/*void sweepAll(){
  sweepServo(servo1);
  sweepServo(servo2);
  sweepServo(servo3);
  delay(2000);
}*/
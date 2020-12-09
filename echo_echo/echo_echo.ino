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
  state 1 =  session
  state 2 = all together
  state 3 = random session
*/
byte state = 2;
int parsedValue = 0;

Servo servo1;
Servo servo2;
Servo servo3;

int capThreshold = 3500;
int longPause = 6000;
int shortPause = 3000;

int pos = 0;
int oldPos = 0;
int startPos = 90;
int endPos = 120;

int servoSpeed = 1;
int updateInterval = 15;
bool servosDetached;
bool movingForward = false;

bool capPressed = false;


//unsigned long previousMillis = 0;
//long interval = 1000;


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
  //long currentMillis = millis();
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
    case 1: 
      total1 = cs_4_2.capacitiveSensor(30);
      Serial.println(total1);
      if (total1 > capThreshold && capPressed == false){
        capPressed = true;
        Serial.println("Cap Button Pressed");
      }
      if(capPressed == true){
        servoSession(longPause);
        capPressed = false;
      }
    break;
    case 2:
    total1 = cs_4_2.capacitiveSensor(30);
    Serial.println(total1);
    if (total1 > capThreshold && capPressed == false){
        capPressed = true;
        Serial.println("Cap Button Pressed");
      }
      if(capPressed == true){
        sweepAll(100);
        capPressed = false;
      }
    break;
    default:
      servo1.write(0);
      servo2.write(0);
      servo3.write(0);
  }
}

//Function to sweep a Servo from Start to Endposition and Back
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
 
void servoSession(int longPause){
  pressButton(servo1);
  delay(longPause);
  pressButton(servo2);
  delay(longPause);
  pressButton(servo3);
  movingForward = !movingForward;
}

void sweepAll(int longPause){
  pressMultiButtons();
  movingForward = !movingForward;
}
void sweepAll(){
  sweepServo(servo1);
  sweepServo(servo2);
  sweepServo(servo3);
  delay(2000);
}
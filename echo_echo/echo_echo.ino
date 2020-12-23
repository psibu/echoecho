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

int capThreshold = 5000;
int servoDelay = 1000;
int longPause = 4000;
int shortPause = 1000;
int waitfactor = 0;


int pos = 0;
int oldPos = 0;
long previousMillis = 0;
const int interval = 20;



int startPos = 90;
int endPos = 120;

int servoSpeed = 1;
int updateInterval = 10;
bool servosDetached;
bool movingForward = false;

bool capPressed = false;
bool lastCapPressed = true;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

long total1;

//smoothing vars sensor
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int totalSmooth = 0;                  // the running total
int average = 0;                // the average

String description = "text";
String combi = "";



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
//set smoothing positions to 0
for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  } 
}

void loop(){
  //unsigned long currentMillis = millis();
  bool reading = capPressed;
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

    ////////////////////////////////////////////  CASE 1 Button / Waiting   //////////////////////////////////////////////////////////////
    case 1: 
      total1 = cs_4_2.capacitiveSensor(30);
      description = "Cap val: ";
      average = total1;
     // average = smoothCapValues(total1); 
      combi = description + average;
      Serial.println(average);

      
      if (reading != lastCapPressed){
        lastDebounceTime = millis();
      }

      if(average < capThreshold && millis() - lastDebounceTime > debounceDelay){
        Serial.println("Cap Pressed");
        if(reading != capPressed){
          capPressed = reading;
          if(capPressed == true){
             //movingForward = !movingForward;
             state =  2;
          }
        }
      }
      lastCapPressed = reading;

  // press cap...
  // if thresahold bigger move motor once 
  // debounce, so it moves only once

    //button = cappressed 
    //led = motor move once


    // if (average > capThreshold && capPressed == false){
      
       
     
     /* if(capPressed == true){
        servoSession(servoDelay);
        capPressed = false;
      }*/
    break;
    case 2:
        Serial.println("////////////////////////////////////////////");
        pressButton(servo1); 
        state = 1;
    break;

    ////////////////////////////////////////////  CASE 2 Button & ALL   //////////////////////////////////////////////////////////////
    case 3:
    total1 = cs_4_2.capacitiveSensor(300);
    description = "Cap val: ";
    average = smoothCapValues(total1);
    combi = description + average;
    Serial.println(combi);
    
    if (average < capThreshold && capPressed == false){
        capPressed = true;
        Serial.println("Cap Button Pressed");
        //state = 4;
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


//////////////////////////////////////////////  SERVO CONTROLL   ////////////////////////////////////////////
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
void servoSession(int _delay){
  pressButton(servo1);
  //delay(_delay);
  pressButton(servo2);
  //delay(_delay);
  pressButton(servo3);
  //movingForward = !movingForward;  
  /*delay(servoDelay * waitfactor);
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


//calculations
int smoothCapValues(long capVal){
   totalSmooth = totalSmooth - readings[readIndex];
    readings[readIndex] = capVal;
    totalSmooth = totalSmooth + readings[readIndex];
    readIndex = readIndex + 1;
    if (readIndex >= numReadings) {
      readIndex = 0;
    }
    average = totalSmooth / numReadings;
    delay(1);        
    return(average);
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

#include <Servo.h>
#include <CapacitiveSensor.h>

//ignoring the whole servo class for now

class MyServo{
  private: 
    Servo servo;
    byte pin;
    byte position = 0;
    byte state = 0;
    byte increment = 1;
    byte updateInterval;
    unsigned long lastUpdate = 0; 
    byte sweepState = 0;
   
    bool finished;
    bool hasStarted;
    bool moving = false;
    
  public:
    MyServo(byte pin, byte position){
      this->pin = pin;
      this->position = position;
      finished = false;
      hasStarted = false;
    }
    
  void init(){
    servo.attach(pin);
    servo.write(position);
  }
  void detatch(){
    servo.detach();
  }

  byte getState(){
     if (position == 90){
      state = 1;
    }else if(position == 0){
      state = 0;
    }
    return state;
  }
  byte getPosition(){
    return position;
  }
  
  void sweep(){
      for (position = 0; position <= 180; position += increment) { 
      servo.write(position);              
      delay(15); 
    }  
    for (position = 180; position >= 0; position -= increment) { 
      servo.write(position);              
      delay(15); 
    } 
<<<<<<< HEAD

    

=======

    

>>>>>>> parent of f3b46b3... Merge branch 'ESP'
    /*
      if(position >= 90){
        hasStarted = true;
        Serial.println("The Motor is moving back towards 0");
        increment = -increment;
      }*/
   } 

   bool isFinished(){
     if(hasStarted && position <= 0){
     finished = true;
    }
     return finished;
   }

   void reset(){
     finished = false;
     hasStarted = false;
     position = 0;
     increment = -increment;
     Serial.println("Reset has happened my position is" + position);
   }
};  

class RecordButton{
  private: 
    byte pin;
    byte state;
  public:
    RecordButton(byte pin){
      this->pin = pin;
      state = 0;
      }  

  void init() {
    pinMode(pin, INPUT_PULLUP);
    update();
    }
  void update(){
    if (digitalRead(pin) == LOW){
        state = 1;
    }else if(digitalRead(pin) == HIGH){
        state = 0;
    }
  }
  byte getState(){
    update();
    return state;
  }
};
<<<<<<< HEAD
<<<<<<< HEAD
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
=======

RecordButton b1(2);
//MyServo s1(9,0);
>>>>>>> parent of f3b46b3... Merge branch 'ESP'

bool moveFirstServo = false;

<<<<<<< HEAD
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
=======
Servo noClassServoOne;
Servo noClassServoTwo;
Servo noClassServoThree;
int pos = 90;  
byte increment = 8;
>>>>>>> parent of f3b46b3... Merge branch 'ESP'

CapacitiveSensor cs_4_2 = CapacitiveSensor(4,2);


<<<<<<< HEAD

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
=======
void setup() {
  Serial.begin(9600);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  //s1.init();
  b1.init();
  noClassServoOne.attach(9);
  noClassServoTwo.attach(10);
  noClassServoThree.attach(11);
}

void loop() {  
  
long start = millis();
long total1 = cs_4_2.capacitiveSensor(30);
Serial.println(total1);

if(total1 >= 1900){
  noClassServoOne.attach(9);
  noClassServoTwo.attach(10);
  noClassServoThree.attach(11);
  sweepServo(noClassServoOne);
  delay(2000);
  sweepServo(noClassServoOne);
  delay(500);
  sweepServo(noClassServoTwo);
  delay(2000); 
  sweepServo(noClassServoTwo);
  delay(500);
  sweepServo(noClassServoThree);
  delay(2000); 
  sweepServo(noClassServoThree);
}else{
  noClassServoOne.detach();
  noClassServoTwo.detach();
  noClassServoThree.detach();
}
=======

RecordButton b1(2);
//MyServo s1(9,0);

bool moveFirstServo = false;

Servo noClassServoOne;
Servo noClassServoTwo;
Servo noClassServoThree;
int pos = 90;  
byte increment = 8;

CapacitiveSensor cs_4_2 = CapacitiveSensor(4,2);


void setup() {
  Serial.begin(9600);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  //s1.init();
  b1.init();
  noClassServoOne.attach(9);
  noClassServoTwo.attach(10);
  noClassServoThree.attach(11);
}

void loop() {  
  
long start = millis();
long total1 = cs_4_2.capacitiveSensor(30);
Serial.println(total1);

if(total1 >= 1900){
  noClassServoOne.attach(9);
  noClassServoTwo.attach(10);
  noClassServoThree.attach(11);
  sweepServo(noClassServoOne);
  delay(2000);
  sweepServo(noClassServoOne);
  delay(500);
  sweepServo(noClassServoTwo);
  delay(2000); 
  sweepServo(noClassServoTwo);
  delay(500);
  sweepServo(noClassServoThree);
  delay(2000); 
  sweepServo(noClassServoThree);
}else{
  noClassServoOne.detach();
  noClassServoTwo.detach();
  noClassServoThree.detach();
}
>>>>>>> parent of f3b46b3... Merge branch 'ESP'
/*
  if (b1.getState() == 1){  
    noClassServoOne.attach(9);
    noClassServoTwo.attach(10);
    noClassServoThree.attach(11);
    sweepServo(noClassServoOne);
    delay(2000);
    sweepServo(noClassServoOne);
    delay(500);
    sweepServo(noClassServoTwo);
    delay(2000); 
    sweepServo(noClassServoTwo);
    delay(500);
    sweepServo(noClassServoThree);
    delay(2000); 
    sweepServo(noClassServoThree);
  /*if(moveFirstServo == true){
    s1.sweep();
    /*if(s1.isFinished()){
      s1.reset();
      moveFirstServo = false;
     // delay(1000);
      
<<<<<<< HEAD
>>>>>>> parent of f3b46b3... Merge branch 'ESP'
  }
    
}
<<<<<<< HEAD

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
=======
=======
  }
    
}
>>>>>>> parent of f3b46b3... Merge branch 'ESP'
}else{
   noClassServoOne.detach();
  noClassServoTwo.detach();
  noClassServoThree.detach();
<<<<<<< HEAD
>>>>>>> parent of f3b46b3... Merge branch 'ESP'
}
*/
}

<<<<<<< HEAD

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
=======
void sweepServo (Servo s){
>>>>>>> parent of f3b46b3... Merge branch 'ESP'
=======
}
*/
}

void sweepServo (Servo s){
>>>>>>> parent of f3b46b3... Merge branch 'ESP'

 for(pos = 90; pos >= 0; pos -= increment)  
  {                                 
    s.write(pos);        
    delay(15);                      
  } 
  for(pos = 0; pos <=90; pos += increment)   
  {                                
    s.write(pos);              
    delay(15);                     
  } 

}
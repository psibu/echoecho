#include <Servo.h>
//include <Arduino.h>
//#include <MyServo.h>
//#include <RecordButton.h>
//#define BUTTON_PIN 2;

#define SETUP 0;
#define USERINPUT 1;
#define AUTOMODE 2;


class MyServo{
  private: 
    Servo servo;
    byte pin;
    byte position;
    byte state = 0;
    int increment = 5;
    int updateInterval;
    unsigned long lastUpdate = 0; 
    int sweepState = 0;
    bool finished;
    bool hasStarted;
    //long previousMillis;
    //long preventSoftResetInterval = 4000;
   // unsigned long sweepDelay = 1000;
    
    
  public:
    MyServo(byte pin, byte position){
      this->pin = pin;
      this->position = position;
      finished = false;
      hasStarted = false;
      //previousMillis = 0;
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
  int getPosition(){
    return position;
  }
  
  void moveServoToPos(byte pos){
      servo.write(pos);
    }

  void sweep(int speed){
    if (millis() - lastUpdate > speed){
      lastUpdate = millis();
      Serial.println("The Motor is moving towards 90");
      position  = position + increment;
      servo.write(position);
      if(position >= 90){
        hasStarted = true;
        Serial.println("The Motor is moving back towards 0");
        Serial.println("the actual position is");
        increment = -increment;
      }
      //Serial.println(position);
    }  
   } 

   bool isFinished(){
     if(hasStarted && position == 0){
     finished = true;
     }
     return finished;
   }

   void reset(){
     finished = false;
     hasStarted = false;
   }
};  

class RecordButton{
  private: 
    byte pin;
    byte state;
   //byte lastReading;
   // unsigned long lastDebounceTime = 0;
   // unsigned long debounceDelay = 500;
  public:
    RecordButton(byte pin){
      this->pin = pin;
      state = 0;
      //lastReading = LOW;
      //init();
      }  
  void init() {
    pinMode(pin, INPUT_PULLUP);
    update();
    }
  void update(){
   // state = digitalRead(pin);
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


RecordButton b1(2);
MyServo s1(9,0);
//MyServo s2(10,90);
MyServo s3(8,90);

unsigned long lastMillis = 0;
unsigned long sweepDelay = 2000;
unsigned long preventSoftResetInterval = 4000;

bool moveServo = false;

void setup() {
  Serial.begin(9600);
  b1.init();
  s1.init();
 // s2.init();
}

void loop() {  
  if (b1.getState() == 1){  
    moveServo = true;
    Serial.println("Move Servo is true");
  }

  if(moveServo == true){
    s1.sweep(20);
    if(s1.isFinished()){
      moveServo = false;
      s1.reset();
    }
    Serial.println("Move Servo is false");
  }

  
}
  
  
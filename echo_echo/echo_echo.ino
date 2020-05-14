#include <Servo.h>
//include <Arduino.h>
//#include <MyServo.h>
//#include <RecordButton.h>
//#define BUTTON_PIN 2;

class MyServo{
  private: 
    Servo servo;
    byte pin;
    byte position;
    byte increment;
    int updateInterval;
    unsigned long lastUpdate; 
    //int speed;
  public:
    MyServo(byte pin, byte position){
      this->pin = pin;
      this->position = position;
      //this->interval = interval;
      //init();
    }

  void init(){
    servo.attach(pin);
    servo.write(position);
  }
  void detatch(){
    servo.detach();
  }

  void moveServoToPos(byte pos){
    servo.write(pos);
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


//MyServo s2(10,90);
#define servo1Pin 9
#define servo1Pos 90

RecordButton b1(2);
MyServo s1(9,90);

void setup() {
  Serial.begin(9600);
  b1.init();
  s1.init();
}
void loop() { 
  Serial.println(b1.getState());
 if (b1.getState() == 1){
   s1.moveServoToPos(90);
 }else if(b1.getState() == 0){
   s1.moveServoToPos(0);
 }
}





















/*void moveServoNrToPos(int servoNr, int pos) {
  myServos[servoNr].write(pos);
}*/

/*void moveFirstServo() {
  if (buttonValue() == 0) {
    moveServoNrToPos(0, 180);
  }else if (buttonValue() == 1){
    moveServoNrToPos(0,90);
}
}*/
/*void moveSecondServo() {
  if (servo1Active == HIGH && (currentMillis - previousMillis >= interval)) {
    moveServoNrToPos(1, 180);
    previousMillis = currentMillis;
    servo1Active = LOW;
  } else if (servo1Active == LOW) {
    moveServoNrToPos(1, 90);
  }*/

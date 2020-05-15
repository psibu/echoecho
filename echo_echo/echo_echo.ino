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
    int interval;
    //byte increment;
    //int updateInterval;
    unsigned long lastUpdate; 
    //int speed;
  public:
    MyServo(byte pin, byte position){
      this->pin = pin;
      this->position = position;
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

RecordButton b1(2);
MyServo s1(9,90);
MyServo s2(10,90);
MyServo s3(8,90);

long previousMillis = 0;
long preventSoftResetInterval = 4000;


void setup() {
  Serial.begin(9600);
  b1.init();
  s1.init();
//s2.init();
//s3.init();
}
void loop() { 
  Serial.println(b1.getState()); 
  unsigned long currentMillis = millis();
  if (b1.getState() == 1){ 
    s1.moveServoToPos(90);
    if(currentMillis - previousMillis >= preventSoftResetInterval){
     s1.moveServoToPos(0);
    }
    //s2.moveServoToPos(0);
    //s3.moveServoToPos(120);
  }else if(b1.getState() == 0){
    previousMillis = currentMillis;
    s1.moveServoToPos(0);
    //s2.moveServoToPos(90);
    //s3.moveServoToPos(30);
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


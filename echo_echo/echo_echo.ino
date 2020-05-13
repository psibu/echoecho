#include <Servo.h>
//include <Arduino.h>
//#include <MyServo.h>
//#include <RecordButton.h>
#define BUTTON_PIN 2;

class MyServo{
  private: 
    Servo servo;
    byte pin;
    int position;
    int speed;
  public:
    MyServo(byte pin, byte position){
      this->pin = pin;
      //this->speed = speed;
      this->position = position;
      init();
      //moveServoToPos();
    }

  void init(){
    servo.attach(pin);
    servo.write(position);
  }

  void moveServoToPos(int pos){
    servo.write(pos);
  }
};  

class RecordButton{
  
  private: 
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 500;
  
  public:
    RecordButton(byte pin){
      this->pin = pin;
      lastReading = LOW;
      //init();
      }
      
  void init() {
    pinMode(pin, INPUT_PULLUP);
    update();
    }
  void update(){
    byte newReading = digitalRead(pin);
    if (newReading != lastReading){
        lastDebounceTime = millis();
      }

    if (millis() - lastDebounceTime > debounceDelay){
      state = newReading;
    }  
    lastReading = newReading;
  }

  byte getState(){
    update();
    return state;
  }
};



MyServo s1(9,90);
//MyServo s2(10,90);
RecordButton b1(1);

void setup() {
  Serial.begin(9600);
  s1.init();
 // s2.init();
  b1.init();
 // pinMode(recordButtonPin, INPUT_PULLUP);
  /*for (int i = 0; i < SERVONUMBER; i++) {
  myServos[i].attach(9+i);
  myServos[i].write(servoPosition);
  Serial.println(i);
}*/
}
void loop() { 
  Serial.println(b1.getState());
  if(b1.getState() == 0){
    s1.moveServoToPos(90);
  }else{
    s1.moveServoToPos(10);
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

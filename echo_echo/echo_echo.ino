#include <Servo.h>
#include <MyServo.h>
#include <RecordButton.h>
#define BUTTON_PIN 2;

RecordButton button1(BUTTON_PIN);
MyServo s1();

//const int recordButtonPin = 2;
//const int SERVONUMBER = 3;
//Servo myServos[SERVONUMBER];

//int state = 0;
//unsigned long currentMillis = 0;
//unsigned long previousMillis = 0;
//unsigned long interval = 5000;


void setup() {
  //Serial.begin(9600);
 // pinMode(recordButtonPin, INPUT_PULLUP);
  
  /*for (int i = 0; i < SERVONUMBER; i++) {
  myServos[i].attach(9+i);
  myServos[i].write(servoPosition);
  Serial.println(i);
}*/
}

void loop() { 
// currentMillis = millis();
 //moveFirstServo();
 // moveSecondServo();
//  Serial.print(state);

//if(button1.isPressed)
//servo1on
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

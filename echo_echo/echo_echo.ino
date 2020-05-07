#include <Servo.h>
const int recordButtonPin = 2;
const int SERVONUMBER = 3;
Servo myServos[SERVONUMBER];
int servoPosition = 90;

int state = 0;

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long interval = 5000;


void setup() {
  Serial.begin(9600);
  pinMode(recordButtonPin, INPUT_PULLUP);
  for (int i = 0; i < SERVONUMBER; i++) {
  myServos[i].attach(9+i);
  myServos[i].write(servoPosition);
  Serial.println(i);
}
}

void loop() {
 currentMillis = millis();
 moveFirstServo();
 // moveSecondServo();
//  Serial.print(state);
  Serial.print(buttonValue());
}



void moveServoNrToPos(int servoNr, int pos) {
  myServos[servoNr].write(pos);
}

int buttonValue() {
  int recordButtonValue = digitalRead(recordButtonPin);
  return recordButtonValue;
}

void moveFirstServo() {
  if (buttonValue() == 0) {
    moveServoNrToPos(0, 180);
  }else if (buttonValue() == 1){
    moveServoNrToPos(0,90);
}
}
/*void moveSecondServo() {
  if (servo1Active == HIGH && (currentMillis - previousMillis >= interval)) {
    moveServoNrToPos(1, 180);
    previousMillis = currentMillis;
    servo1Active = LOW;
  } else if (servo1Active == LOW) {
    moveServoNrToPos(1, 90);
  }*/

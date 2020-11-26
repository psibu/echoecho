#include <CapacitiveSensor.h>
#include <Servo.h>

#define IN D4
#define OUT D2
CapacitiveSensor cs_4_2 = CapacitiveSensor(IN, OUT);

Servo servo1;
Servo servo2;
Servo servo3;



int pos = 120;
byte increment = 1;
bool servosDetached;



void setup() {
  Serial.begin(9600);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);

  servo1.write(pos);
  servo2.write(pos);
  servo3.write(pos);

  servo1.attach(D5);
  servo2.attach(D6);
  servo3.attach(D7);

  servosDetached = false;
}

void loop() {

  long total1 = cs_4_2.capacitiveSensor(30);
  Serial.println(servo1.read());
  // Serial.println(servosDetached);

  if (total1 > 2500) {
    Serial.println("Cap Button Pressed");

    if ( servosDetached == true) {
      servo1.write(pos);
      servo2.write(pos);
      servo3.write(pos);
      servo1.attach(D5);
      servo2.attach(D6);
      servo3 .attach(D7);
      servosDetached = false;
    }

    servoSession(4000, 2000);

  } else {

    servo1.detach();
    servo2.detach();
    servo3.detach();
    servosDetached = true;
  }

}

void sweepServo(Servo s) {
  for (pos = 120; pos >= 90; pos -= increment) {
    s.write(pos);
    delay(5);
  }
  for (pos = 90; pos <= 120; pos += increment) {
    s.write(pos);
    delay(5);
  }
}

void servoSession(int longPause, int shortPause) {
  Serial.println("Servosession reached");
  sweepServo(servo1);
  delay(longPause);
  sweepServo(servo1);
  delay(shortPause);
  sweepServo(servo2);
  delay(longPause);
  sweepServo(servo2);
  delay(shortPause);
  sweepServo(servo3);
  delay(longPause);
  sweepServo(servo3);
}

#include <CapacitiveSensor.h>
#include <Servo.h>

#define IN D4
#define OUT D2
CapacitiveSensor cs_4_2 = CapacitiveSensor(IN,OUT);

Servo servo1;
Servo servo2;
Servo servo3;

int pos = 90;
byte increment = 5;
bool servosDetached;

void setup() {
  Serial.begin(9600); 
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
 /* servo1.attach(D5);
  servo2.attach(D6);
  servo3.attach(D7);*/
  servosDetached = false;
}

void loop() {
  long total1 = cs_4_2.capacitiveSensor(30);
   Serial.println(total1);
   Serial.println(servosDetached);
   
    if(total1 > 4000) {
      Serial.println("Cap Button Pressed");
      
      if( servosDetached == true){ 
        servo1.attach(D5);
        servo2.attach(D6);
        servo3 .attach(D7);
        servosDetached = false;
      }

      //servoSession(2000,500);
      sweepAll();

  }else{
    servo1.detach();
    servo2.detach();
    servo3.detach();
    servosDetached = true;
  }
}

void sweepServo(Servo s){
  for(pos = 90; pos >= 0; pos -= increment){
   s.write(pos);
   delay(15); 
  }
  for(pos = 0; pos <= 90; pos += increment){
    s.write(pos);
    delay(15);
  }
}

void servoSession(int longPause, int shortPause){
  Serial.println("Servosession reached");
  sweepServo(servo1);
  //delay(longPause);
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

void sweepAll(){
  
  sweepServo(servo1);
  sweepServo(servo2);
  sweepServo(servo3);
  
  }

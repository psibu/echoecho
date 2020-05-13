
/* MyServo.h - Library for controlling Servo
  Created by Peter Buczkowski, Mai 12, 2020.
  peterbuczkowski.com
  Released into the public domain.*/

#ifndef MyServo_h
#define MyServo_h

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

  void init()  {
    servo.attach(pin);
    servo.write(position);
  }

  void moveServoToPos(int pos){
    servo.write(pos)
  }
};  

#endif
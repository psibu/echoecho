class MyServo{
  private: 
    Servo servo;
    byte pin;
    int position;
    int speed;
    
  
  public:
    MyServo(byte pin, byte position, byte speed){
      this->pin = pin;
      this->speed = speed;
      this->position = position;
      init();
    }

  void init()  {
    servo.attach(pin);
    servo.write(position);
  }

  void moveServoToPos(int pos){
    servo.write(pos)
  }
};  
  

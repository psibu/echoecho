#include <Servo.h>
#include <CapacitiveSensor.h>

//ignoring the whole servo class for now

class MyServo{
  private: 
    Servo servo;
    byte pin;
    byte position = 0;
    byte state = 0;
    byte increment = 1;
    byte updateInterval;
    unsigned long lastUpdate = 0; 
    byte sweepState = 0;
   
    bool finished;
    bool hasStarted;
    bool moving = false;
    
  public:
    MyServo(byte pin, byte position){
      this->pin = pin;
      this->position = position;
      finished = false;
      hasStarted = false;
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
  byte getPosition(){
    return position;
  }
  
  void sweep(){
      for (position = 0; position <= 180; position += increment) { 
      servo.write(position);              
      delay(15); 
    }  
    for (position = 180; position >= 0; position -= increment) { 
      servo.write(position);              
      delay(15); 
    } 

    

    /*
      if(position >= 90){
        hasStarted = true;
        Serial.println("The Motor is moving back towards 0");
        increment = -increment;
      }*/
   } 

   bool isFinished(){
     if(hasStarted && position <= 0){
     finished = true;
    }
     return finished;
   }

   void reset(){
     finished = false;
     hasStarted = false;
     position = 0;
     increment = -increment;
     Serial.println("Reset has happened my position is" + position);
   }
};  

class RecordButton{
  private: 
    byte pin;
    byte state;
  public:
    RecordButton(byte pin){
      this->pin = pin;
      state = 0;
      }  

  void init() {
    pinMode(pin, INPUT_PULLUP);
    update();
    }
  void update(){
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
//MyServo s1(9,0);

bool moveFirstServo = false;

Servo noClassServoOne;
Servo noClassServoTwo;
Servo noClassServoThree;
int pos = 90;  
byte increment = 8;

CapacitiveSensor cs_4_2 = CapacitiveSensor(4,2);


void setup() {
  Serial.begin(9600);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  //s1.init();
  b1.init();
  noClassServoOne.attach(9);
  noClassServoTwo.attach(10);
  noClassServoThree.attach(11);
}

void loop() {  
  
long start = millis();
long total1 = cs_4_2.capacitiveSensor(30);
Serial.println(total1);

if(total1 >= 1900){
  noClassServoOne.attach(9);
  noClassServoTwo.attach(10);
  noClassServoThree.attach(11);
  sweepServo(noClassServoOne);
  delay(2000);
  sweepServo(noClassServoOne);
  delay(500);
  sweepServo(noClassServoTwo);
  delay(2000); 
  sweepServo(noClassServoTwo);
  delay(500);
  sweepServo(noClassServoThree);
  delay(2000); 
  sweepServo(noClassServoThree);
}else{
  noClassServoOne.detach();
  noClassServoTwo.detach();
  noClassServoThree.detach();
}
/*
  if (b1.getState() == 1){  
    noClassServoOne.attach(9);
    noClassServoTwo.attach(10);
    noClassServoThree.attach(11);
    sweepServo(noClassServoOne);
    delay(2000);
    sweepServo(noClassServoOne);
    delay(500);
    sweepServo(noClassServoTwo);
    delay(2000); 
    sweepServo(noClassServoTwo);
    delay(500);
    sweepServo(noClassServoThree);
    delay(2000); 
    sweepServo(noClassServoThree);
  /*if(moveFirstServo == true){
    s1.sweep();
    /*if(s1.isFinished()){
      s1.reset();
      moveFirstServo = false;
     // delay(1000);
      
  }
    
}
}else{
   noClassServoOne.detach();
  noClassServoTwo.detach();
  noClassServoThree.detach();
}
*/
}

void sweepServo (Servo s){

 for(pos = 90; pos >= 0; pos -= increment)  
  {                                 
    s.write(pos);        
    delay(15);                      
  } 
  for(pos = 0; pos <=90; pos += increment)   
  {                                
    s.write(pos);              
    delay(15);                     
  } 

}
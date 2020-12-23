class RecordButton{
  
  private: 
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
  
  public:
    RecordButton(byte pin){
      this->pin = pin;
      lastReading = LOW;
      init();
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

  boolean isPressed() {
    return (getState() == HIGH);
  }
};

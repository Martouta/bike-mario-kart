#define pinLed 13
#define pinHallSensor 3

double previousTimeMagnetDetected = 0;
boolean beforeThereWasMagnet = false;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinHallSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  const unsigned int hallValue = digitalRead(pinHallSensor);

  if(hallValue == LOW) {
    digitalWrite(pinLed, HIGH);
    if(previousTimeMagnetDetected == 0) {
      previousTimeMagnetDetected = micros() / 1000.0;
    } else {
      if (!beforeThereWasMagnet) {
        digitalWrite(pinLed, HIGH);
  
        const double currentTime = micros() / 1000.0;
        
        Serial.println(String("currentTime: ") + currentTime + " - previousTimeMagnetDetected: " + previousTimeMagnetDetected);
        const double periodMillisBetweenRounds = currentTime - previousTimeMagnetDetected;
        Serial.println(String("periodMillisBetweenRounds: ") + periodMillisBetweenRounds);
        const double periodSecondsBetweenRounds = periodMillisBetweenRounds / 1000.0;
        Serial.println(String("periodSecondsBetweenRounds: ") + periodSecondsBetweenRounds);
        const double frequency = 1 / periodSecondsBetweenRounds;
  
        previousTimeMagnetDetected = currentTime;
  
        Serial.println(String("frequency: ") + frequency);
        Serial.println("-----------------");
      }
    }
    beforeThereWasMagnet = true;
  } else {
    digitalWrite(pinLed, LOW);
    beforeThereWasMagnet = false;
  }
}

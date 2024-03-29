#define millisTimeoutStop 1000

double previousTimeMagnetDetected = 0;
boolean beforeThereWasMagnet = false;
double bikeFrequency = 0;

double getSpeedFreq() {
  updateSpeedFrequency();
  return bikeFrequency;
}

void updateSpeedFrequency() {
  const unsigned int hallValue = digitalRead(pinHallSensor);

  #ifndef JOYSTICKSHIELD
    updateSpeedLed(hallValue);
  #endif

  const double currentTime = millis();
  const double periodMillisBetweenRounds = currentTime - previousTimeMagnetDetected;

  if(periodMillisBetweenRounds >= millisTimeoutStop && !beforeThereWasMagnet) {
    resetFrequency();
  } else {
    if(hallValue == LOW) {
      if(isFirstTimeMagnetDetected()) {
        previousTimeMagnetDetected = currentTime;
      } else {
        if (!beforeThereWasMagnet) {
          const double periodSecondsBetweenRounds = periodMillisBetweenRounds / 1000.0;
          bikeFrequency = 1 / periodSecondsBetweenRounds;
          previousTimeMagnetDetected = currentTime;
        }
      }
    }
  }
  beforeThereWasMagnet = !hallValue;
}

boolean isFirstTimeMagnetDetected() {
  return previousTimeMagnetDetected == 0;
}

void resetFrequency() {
  bikeFrequency = 0;
  previousTimeMagnetDetected = 0;
  beforeThereWasMagnet = false;
}

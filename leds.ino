#ifndef JOYSTICKSHIELD
  void updateLEDsGameUnstarted() {
    digitalWrite(pinSpeedLED, LOW);
    digitalWrite(pinRotationLED, HIGH);
  }

  void updateLEDsGameStarted(boolean gameStarted) {
    if (!gameStarted) { return; }

    digitalWrite(pinSpeedLED, HIGH);
    digitalWrite(pinRotationLED, HIGH);
    delay(50);
    digitalWrite(pinSpeedLED, LOW);
    digitalWrite(pinRotationLED, LOW);
  }

  void updateSpeedLed(unsigned int hallValue) {
    if(hallValue == LOW) {
      digitalWrite(pinSpeedLED, HIGH);
    } else {
      digitalWrite(pinSpeedLED, LOW);
    }
  }

  void updateRotationLed() {
    digitalWrite(pinRotationLED, LOW);
  }

  void blinkRotationLed() {
    digitalWrite(pinRotationLED, !digitalRead(pinRotationLED));
  }
#endif

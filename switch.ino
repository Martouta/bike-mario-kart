#ifndef JOYSTICKSHIELD
  struct JoystickCoord {
    int x;
    int y;
  };
  
  struct JoystickCoord leftJoystickValuesFromYaw(float yaw) {
    float filteredYaw = yaw;
    if(filteredYaw > 1.57079633) { // > 90 degrees
      filteredYaw = 1.57079633;
    } else if(filteredYaw < -1.57079633){ // < -90 degrees
      filteredYaw = -1.57079633;
    }
  
    float u = 127.5 * sin(filteredYaw), 
          v = 127.5 * cos(filteredYaw);
  
    struct JoystickCoord leftJoystick;
    leftJoystick.x = round(127.5 + u);
    leftJoystick.y = round(127.5 - v);
    return leftJoystick;
  }
  
  struct JoystickCoord leftJoystickValuesFromAnalogJS() {
    int xPosition = analogRead(A0),
        yPosition = analogRead(A1);
    
    struct JoystickCoord leftJoystick;
    leftJoystick.x = map(xPosition, 0, 1023, 0, 255);
    leftJoystick.y = map(yPosition, 0, 1023, 0, 255);
    return leftJoystick;
  }
  
  
  void sendGameData(float freq, float yaw) {
    sendButtonsData(freq);
    sendLeftJoystickData(freq, yaw);
    
    Joystick.sendState();
  }
  
  void sendLeftJoystickData(float freq, float yaw) {
    const boolean manualLeftJS = (digitalRead(pinSPTDLeftJS) == HIGH);
  
    if (manualLeftJS) {
      // Move from the manual left joystick
      struct JoystickCoord coords = leftJoystickValuesFromAnalogJS();
  
      Joystick.setXAxis(coords.x);
      Joystick.setYAxis(coords.y);
    } else if (freq > 0) {
      // Move from bike
      struct JoystickCoord coords = leftJoystickValuesFromYaw(yaw);
  
      Joystick.setXAxis(coords.x);
      Joystick.setYAxis(coords.y);
    } else {
      // Stay in the center
      Joystick.setXAxis(128);
      Joystick.setYAxis(128);
    }
  }
  
  void sendButtonsData(float freq) {
    Joystick.setButton(4, pressOrReleaseValue(pinButtonL));   // L
    Joystick.setButton(5, pressOrReleaseValue(pinButtonR));   // R
    Joystick.setButton(9, pressOrReleaseValue(pinButtonAdd)); // +
    Joystick.setButton(1, pressOrReleaseValue(pinButtonB));   // B
    Joystick.setButton(2, (((digitalRead(pinButtonA) == LOW) || shouldAccelerate(freq))) ? 1 : 0); // A
  }
#endif

boolean shouldAccelerate(float freq) {
  return freq >= 0.02; // Initial value :)
}

int pressOrReleaseValue(int button) {
  return (digitalRead(button) == LOW) ? 1 : 0;
}

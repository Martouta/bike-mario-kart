struct JoystickCoord {
  int x;
  int y;
};

boolean shouldAccelerate(float freq) {
  return freq >= 0.2; // Initial value :)
}

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

void sendGameData(float freq, float yaw) {
  Joystick.setButton(4, pressOrReleaseValue(pinButtonL));   // L
  Joystick.setButton(5, pressOrReleaseValue(pinButtonR));   // R
  Joystick.setButton(9, pressOrReleaseValue(pinButtonAdd)); // +
  Joystick.setButton(1, pressOrReleaseValue(pinButtonB));   // B
  Joystick.setButton(2, (((digitalRead(pinButtonA) == LOW) || shouldAccelerate(freq))) ? 1 : 0); // A
  

  if (freq > 0) {
    // Move
    struct JoystickCoord coords = leftJoystickValuesFromYaw(yaw);

    Joystick.setXAxis(coords.x);
    Joystick.setYAxis(coords.y);
  } else {
    // Stay in the center
    Joystick.setXAxis(128);
    Joystick.setYAxis(128);
  }
  
  
  Joystick.sendState();
}

int pressOrReleaseValue(int button) {
  return (digitalRead(button) == LOW) ? 1 : 0;
}

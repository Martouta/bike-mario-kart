boolean shouldAccelerate(float freq) {
  return freq >= 0.2; // Initial value :)
}

void sendGameData(float freq, float yaw) {
  Joystick.setButton(4, pressOrReleaseValue(pinButtonL));   // L
  Joystick.setButton(5, pressOrReleaseValue(pinButtonR));   // R
  Joystick.setButton(9, pressOrReleaseValue(pinButtonAdd)); // +
  Joystick.setButton(1, pressOrReleaseValue(pinButtonB));   // B
  Joystick.setButton(2, (((digitalRead(pinButtonA) == LOW) || shouldAccelerate(freq))) ? 1 : 0); // A
  

  if (freq > 0) {
    // Move
    float filteredYaw = yaw;
    if(filteredYaw > 1.57079633) { // > 90 degrees
      filteredYaw = 1.57079633;
    } else if(filteredYaw < -1.57079633){ // < -90 degrees
      filteredYaw = -1.57079633;
    }
    
    float u = 128 * sin(filteredYaw), 
          v = 128 * cos(filteredYaw);
    int x = 128 + ((int) u),
        y = 128 - ((int) v);

    Joystick.setXAxis(x);
    Joystick.setYAxis(y);
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

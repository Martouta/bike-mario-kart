#ifdef JOYSTICKSHIELD
  void sendGameDataFromJoystickShield(float freq) {
    Joystick.setButton(2, (((digitalRead(RIGHT_BTN) == LOW) || shouldAccelerate(freq))) ? 1 : 0); // A
    Joystick.setButton(1, pressOrReleaseValue(DOWN_BTN));     // B
    Joystick.setButton(4, pressOrReleaseValue(LEFT_BTN));     // L
    Joystick.setButton(5, pressOrReleaseValue(UP_BTN));       // R
    Joystick.setButton(9, pressOrReleaseValue(F_BTN));        // +
  
    int xPosition = analogRead(JOYSTICK_AXIS_X),
        yPosition = analogRead(JOYSTICK_AXIS_Y);
  
    Joystick.setXAxis(map(xPosition, 0, 1023, 0, 255));
    Joystick.setYAxis(map(yPosition, 0, 1023, 255, 0));
  
    Joystick.sendState();
  }
#endif

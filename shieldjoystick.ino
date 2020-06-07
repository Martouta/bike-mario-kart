#ifdef JOYSTICKSHIELD
  void sendGameDataFromJoystickShield() {
    Joystick.setButton(2, pressOrReleaseValue(RIGHT_BTN));    // A // TODO: Also accept real frequency!!
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

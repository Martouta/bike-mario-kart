SwitchJoystick_ switchJoystick;

void initializeSwitch() {
  switchJoystick.begin(false);
}

void sendGameData() {
  switchJoystick.setXAxis(gameData.leftJS.x);
  switchJoystick.setYAxis(gameData.leftJS.y);

  switchJoystick.setButton(2, gameData.btnA);
  switchJoystick.setButton(1, gameData.btnB);
  switchJoystick.setButton(4, gameData.btnL);
  switchJoystick.setButton(5, gameData.btnR);
  switchJoystick.setButton(9, gameData.btnAdd);

  switchJoystick.sendState();
}

struct JoystickCoord {
  int x;
  int y;
};

struct GameData {
  boolean btnA;
  boolean btnB;
  boolean btnL;
  boolean btnR;
  boolean btnAdd;
  struct JoystickCoord leftJS;
};

struct GameData gameData = { false, false, false, false, false, 128, 128 };


void updateGameData() {
  float freq = (float) getSpeedFreq();

   updateButtonsData(freq);
   updateLeftJoystickData(freq);
}

void updateButtonsData(float freq) {
  gameData.btnA   = (digitalRead(pinButtonA) == LOW) || (shouldAccelerate(freq) ? 1 : 0);
  gameData.btnB   = pressOrReleaseValue(pinButtonB);
  gameData.btnL   = pressOrReleaseValue(pinButtonL);
  gameData.btnR   = pressOrReleaseValue(pinButtonR);
  gameData.btnAdd = pressOrReleaseValue(pinButtonAdd);
}

void updateLeftJoystickData(float freq) {
  #ifdef JOYSTICKSHIELD
    gameData.leftJS = leftJSValuesFromShield();
  #else
    const boolean manualLeftJS = (digitalRead(pinSPTDLeftJS) == HIGH);

    if (manualLeftJS) {
      // Move from the manual left joystick
      gameData.leftJS = leftJSValuesFromIndividualAnalog();
    } else if (freq > 0) {
      // Move from bike
      float yaw = getYaw();
      gameData.leftJS = leftJoystickValuesFromYaw(yaw);
    } else {
      // Stay in the center
      gameData.leftJS.x = 128;
      gameData.leftJS.y = 128;
    }
  #endif
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

struct JoystickCoord leftJSValuesFromIndividualAnalog() {
  int xPosition = analogRead(pinLAnalogX),
      yPosition = analogRead(pinLAnalogY);

  struct JoystickCoord leftJoystick;
  leftJoystick.x = map(xPosition, 0, 1023, 0, 255);
  leftJoystick.y = map(yPosition, 0, 1023, 0, 255);
  return leftJoystick;
}

struct JoystickCoord leftJSValuesFromShield() {
  int xPosition = analogRead(pinLAnalogX),
      yPosition = analogRead(pinLAnalogY);

  struct JoystickCoord leftJoystick;
  leftJoystick.x = map(xPosition, 0, 1023, 0, 255);
  leftJoystick.y = map(yPosition, 0, 1023, 255, 0);
  return leftJoystick;
}


boolean shouldAccelerate(float freq) {
  return freq >= 0.02; // Initial value :)
}

int pressOrReleaseValue(int button) {
  return (digitalRead(button) == LOW) ? 1 : 0;
}

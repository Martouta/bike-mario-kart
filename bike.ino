#include "config.h"

#ifdef JOYSTICKSHIELD
  #define pinButtonR      (uint8_t)2 // Up button
  #define pinButtonA      (uint8_t)3 // Right button
  #define pinButtonB      (uint8_t)4 // Down button
  #define pinButtonL      (uint8_t)5 // Left button
  #define pinButtonAdd    (uint8_t)7 // F button
  #define pinHallSensor   (uint8_t)13
#else
  #define pinInterruptMPU (uint8_t)0
  #define pinButtonB      (uint8_t)1
  // Pins 2 and 3 and for SCA and SCL of the MPU6050
  #define pinButtonA      (uint8_t)4
  #define pinButtonAdd    (uint8_t)5
  #define pinButtonR      (uint8_t)6
  #define pinButtonL      (uint8_t)7
  #define pinHallSensor   (uint8_t)8
  #define pinSPTDLeftJS   (uint8_t)9
  #define pinRotationLED  (uint8_t)12
  #define pinSpeedLED     (uint8_t)13
#endif

const uint8_t buttons[] = { pinButtonR, pinButtonA, pinButtonB, pinButtonL, pinButtonAdd };
#define pinLAnalogX    (uint8_t)A0
#define pinLAnalogY    (uint8_t)A1


#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <Wire.h>

#include <SwitchJoystick.h>

boolean gameStarted = false;

void setup() {
  for (int i = 0; i < 5; i++) pinMode(buttons[i], INPUT_PULLUP); // TODO: check what this implies when it isn't using the JoystickShield

  #ifndef JOYSTICKSHIELD
    // pinMode(pinLAnalogX, INPUT); // TODO: check what this implies when it isn't using the JoystickShield
    // pinMode(pinLAnalogY, INPUT); // TODO: check what this implies when it isn't using the JoystickShield
    pinMode(pinSPTDLeftJS, INPUT);

    pinMode(pinSpeedLED, OUTPUT);
    pinMode(pinRotationLED, OUTPUT);

    i2cSetup();
    MPU6050Connect();
  #endif

  pinMode(pinHallSensor, INPUT);
  resetFrequency();
  initializeSwitch();

  #ifndef JOYSTICKSHIELD
    updateLEDsGameUnstarted();
  #endif
}

void loop() {
  // Wait for the A button to start playing.
  if (gameStarted) {
    updateGameData();
    sendGameData();
    delay(50);
  } else {
    updateGameStarted();
    delay(100);
  }
}

void updateGameStarted() {
  gameStarted = checkGameStarted();
  #ifndef JOYSTICKSHIELD
    updateLEDsGameStarted(gameStarted);
  #endif
}

boolean checkGameStarted() {
  return (digitalRead(pinButtonA) == LOW);
}

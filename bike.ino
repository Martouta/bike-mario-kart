#define pinInterruptMPU 0
#define pinHallSensor 8
#define pinSpeedLED 13
#define pinRotationLED 12
#define pinButtonL 7
#define pinButtonR 6
#define pinButtonAdd 5
#define pinButtonA 4
#define pinButtonB 1

#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <Wire.h>

#include <SwitchJoystick.h>

SwitchJoystick_ Joystick;

boolean gameStarted = false;

void setup() {
  pinMode(pinButtonL, INPUT);
  pinMode(pinButtonR, INPUT);
  pinMode(pinButtonAdd, INPUT);
  pinMode(pinButtonA, INPUT);
  pinMode(pinButtonB, INPUT);

  pinMode(pinHallSensor, INPUT);
  resetFrequency();

  pinMode(pinSpeedLED, OUTPUT);
  pinMode(pinRotationLED, OUTPUT);

  Joystick.begin(false);

  i2cSetup();
  MPU6050Connect();
}

void loop() {
  // Wait for the A button to start playing.
  if (gameStarted) {
    sendGameData(((float) getSpeedFreq()), getYaw());
    delay(50);
  } else {
    digitalWrite(pinSpeedLED, LOW);
    digitalWrite(pinRotationLED, HIGH);
    delay(100);
    gameStarted = (digitalRead(pinButtonA) == LOW);
    if (gameStarted) {
      digitalWrite(pinSpeedLED, HIGH);
      digitalWrite(pinRotationLED, HIGH);
      delay(100);
      digitalWrite(pinSpeedLED, LOW);
      digitalWrite(pinRotationLED, LOW);
    }
  }
}

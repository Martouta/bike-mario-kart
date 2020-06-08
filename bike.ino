#define JOYSTICKSHIELD true

#ifdef JOYSTICKSHIELD
  #define UP_BTN          (uint8_t)2
  #define RIGHT_BTN       (uint8_t)3
  #define DOWN_BTN        (uint8_t)4
  #define LEFT_BTN        (uint8_t)5
  #define E_BTN           (uint8_t)6
  #define F_BTN           (uint8_t)7
  #define JOYSTICK_BTN    (uint8_t)8
  #define pinHallSensor   (uint8_t)13
  #define JOYSTICK_AXIS_X (uint8_t)A0
  #define JOYSTICK_AXIS_Y (uint8_t)A1
  int buttons[] = {UP_BTN, DOWN_BTN, LEFT_BTN, RIGHT_BTN, E_BTN, F_BTN, JOYSTICK_BTN};
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
  #define pintLAnalogX    (uint8_t)A0
  #define pintLAnalogY    (uint8_t)A1
#endif


#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <Wire.h>

#include <SwitchJoystick.h>
SwitchJoystick_ Joystick;

boolean gameStarted = false;

void setup() {
  #ifdef JOYSTICKSHIELD
    for (int i; i < 7; i++) pinMode(buttons[i], INPUT_PULLUP);
  #else
    pinMode(pinButtonL, INPUT);
    pinMode(pinButtonR, INPUT);
    pinMode(pinButtonAdd, INPUT);
    pinMode(pinButtonA, INPUT);
    pinMode(pinButtonB, INPUT);

    pinMode(pintLAnalogX, INPUT);
    pinMode(pintLAnalogY, INPUT);
    pinMode(pinSPTDLeftJS, INPUT);

    pinMode(pinSpeedLED, OUTPUT);
    pinMode(pinRotationLED, OUTPUT);

    i2cSetup();
    MPU6050Connect();
  #endif

  pinMode(pinHallSensor, INPUT);
  resetFrequency();
  Joystick.begin(false);
}

void loop() {
  // Wait for the A button to start playing.
  if (gameStarted) {
    #ifdef JOYSTICKSHIELD
     sendGameDataFromJoystickShield((float) getSpeedFreq());
    #else
      sendGameData(((float) getSpeedFreq()), getYaw());
    #endif
    delay(50);
  } else {
    #ifndef JOYSTICKSHIELD
      digitalWrite(pinSpeedLED, LOW);
      digitalWrite(pinRotationLED, HIGH);
    #endif

    delay(100);
    #ifdef JOYSTICKSHIELD
      gameStarted = (digitalRead(RIGHT_BTN) == LOW);
    #else
      gameStarted = (digitalRead(pinButtonA) == LOW);
    #endif

    #ifndef JOYSTICKSHIELD
      if (gameStarted) {
        digitalWrite(pinSpeedLED, HIGH);
        digitalWrite(pinRotationLED, HIGH);
        delay(100);
        digitalWrite(pinSpeedLED, LOW);
        digitalWrite(pinRotationLED, LOW);
      }
    #endif
  }
}

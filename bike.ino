#define pinLed 13
#define pinHallSensor 3

void setup()
{
  pinMode(pinLed, OUTPUT);
  pinMode(pinHallSensor, INPUT);
}

void loop()
{
  const unsigned int hallValue = digitalRead(pinHallSensor);
  
  if(hallValue == LOW)
  {
    digitalWrite(pinLed, HIGH);
  }
  else
  {
    digitalWrite(pinLed, LOW);
  }
}

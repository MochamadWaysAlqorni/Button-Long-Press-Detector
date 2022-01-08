#include <Arduino.h>
#include <ezButton.h>

ezButton button1(0); // create ezButton object that attach to pin 7;
int pwm;
unsigned long pressedTime = 0;
unsigned long releasedTime = 0;

void setup()
{
  Serial.begin(9600);
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop()
{
  button1.loop(); // MUST call the loop() function first

  if (button1.isPressed())
    pressedTime = millis();
  if (button1.isReleased())
  {
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if (pressDuration < 500)
    {
      pwm += 1;
    }

    if (pressDuration > 500)
    {
      pwm += 50;
    }
  }
  if (pwm >= 255)
  {
    pwm = 0;
  }
  analogWrite(5, pwm);
}
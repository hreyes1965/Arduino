/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fade
*/

int fadePin1[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW}; // slow fade
int fadePin2 = 19;      // fast fade
int fadePin3 = 20;      // fast fade reversed
int fadePin4 = 21;      // fast fade
int index1 = 0;
int indexIncrement1 = 1;
int brightness1 = 0;    // brightness for slow fade
int brightness2 = 0;    // brightness for fast fade and reversed fast fade
int speedFastFade = 10;  // how many points to fade the LED by
int speedSlowFade = 5; // how many points to fade the LED by
int fadeDelay = 75;
int blinkDelay = 25;
unsigned long t1 = 0;
unsigned long t2 = 0;

// the setup routine runs once when you press reset:
void setup() {
  // pins to be an output for blinking
  for (int i = 3; i<= 12; i++) {
    pinMode(i, OUTPUT);
  }

  // pins to be an output for fading
  pinMode(fadePin2, OUTPUT);
  pinMode(fadePin3, OUTPUT);
  pinMode(fadePin4, OUTPUT);

  // initialize serial communication:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  index1 += indexIncrement1;
  if (index1 <= 0 || index1 >= 9)
    indexIncrement1 = -indexIncrement1;

  blinkLight();
  fadeLight();
  Serial.println(LOW);
  Serial.println(HIGH);
  Serial.println(brightness1);
  Serial.println(brightness2);
}

void fadeLight() {
  // set the brightness of pins
  //analogWrite(fadePin1, brightness1);
  analogWrite(fadePin2, brightness2);
  analogWrite(fadePin3, (255 - brightness2));
  analogWrite(fadePin4, brightness2);

  // change the brightness for next time through the loop:
  brightness1 = brightness1 + speedFastFade;
  brightness2 = brightness2 + speedSlowFade;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness1 <= 0 || brightness1 >= 255) {
    speedFastFade = -speedFastFade;
    if (brightness1 < 0)
      brightness1 = 0;
    else if (brightness1 > 255)
      brightness1 = 255;
  }

  // reverse the direction of the fading at the ends of the fade:
  if (brightness2 <= 0 || brightness2 >= 255) {
    speedSlowFade = -speedSlowFade;
    if (brightness2 < 0)
      brightness2 = 0;
    else if (brightness2 > 255)
      brightness2 = 255;
  }

  // wait for 50 milliseconds to see the dimming effect
  delay(fadeDelay);
}

void blinkLight() {
  if (fadePin1[index1] == HIGH)
    fadePin1[index1] = LOW;
  else if (fadePin1[index1] == LOW)
    fadePin1[index1] = HIGH;

  digitalWrite(index1 + 3, fadePin1[index1]);
}

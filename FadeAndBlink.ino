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

int ledFade = 9;                // the PWM pin the LED is attached to
int ledFastBlink = 10;          // pin for fast blink
int ledMediumBlink = 11;       // pin for medium blink
int ledSlowBlink = LED_BUILTIN; // pin for slow blink
int brightness = 0;             // how bright the LED is
int fadeAmount = 5;             // how many points to fade the LED by
int fadeDelay = 30;
int slowSynchCounter = 0;       // synch blinking and fading
int slowBlinkReset = 50;
int mediumSynchCounter = 0;     // synch blinking and fading
int mediumBlinkReset = 35;
int fastSynchCounter = 0;       // synch blinking and fading
int fastBlinkReset = 25;

// the setup routine runs once when you press reset:
void setup() {
  // initialize digital pin LED_BUILTIN as an output for blinking
  pinMode(ledSlowBlink, OUTPUT);
  pinMode(ledMediumBlink, OUTPUT);
  pinMode(ledFastBlink, OUTPUT);

  // declare pin 9 to be an output for fading
  pinMode(ledFade, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  fadeLight();
  blinkLight();
}

void blinkLight(){
  if (slowSynchCounter == 0)
    digitalWrite(ledSlowBlink, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(2000);                       // wait for a second
  if (slowSynchCounter == 40)
    digitalWrite(ledSlowBlink, LOW);    // turn the LED off by making the voltage LOW
  //delay(500);                       // wait for a second
  if (mediumSynchCounter == 0)
    digitalWrite(ledMediumBlink, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(2000);                       // wait for a second
  if (mediumSynchCounter == 30)
    digitalWrite(ledMediumBlink, LOW);    // turn the LED off by making the voltage LOW
  //delay(500);                       // wait for a second
  if (fastSynchCounter == 0)
    digitalWrite(ledFastBlink, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(2000);                       // wait for a second
  if (fastSynchCounter == 20)
    digitalWrite(ledFastBlink, LOW);    // turn the LED off by making the voltage LOW
  //delay(500);                       // wait for a second
}

void fadeLight() {
  // set the brightness of pin 9:
  analogWrite(ledFade, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  // wait for 50 milliseconds to see the dimming effect
  delay(fadeDelay);
  
  slowSynchCounter++;
  if (slowSynchCounter == slowBlinkReset)
    slowSynchCounter = 0;

  mediumSynchCounter++;
  if (mediumSynchCounter == mediumBlinkReset)
    mediumSynchCounter = 0;

  fastSynchCounter++;
  if (fastSynchCounter == fastBlinkReset)
    fastSynchCounter = 0;
}

/*
   => this project turns on lights in sequence and
      fade off lights once all of them are on
   => cycle is activated by sound pressure
*/

#include <Adafruit_CircuitPlayground.h>

// pinouts for Adafruits CPGE
int pinLine1 = 6;  // A1
int pinLine2 = 9;  // A2
int pinLine3 = 10; // A3
int pinLine4 = 3;  // A4
int pinLine5 = 2;  // A5
int appState = 1;
int brightness = 0; // from 0 (low) to 255 (high)
int fadeAmount = 5; // how many points to fade the LED by
int fadeDelay = 30;
int stateDelay = 2000;
int flag = 0;
int cycleCount = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize output pins
  pinMode(pinLine1, OUTPUT);
  pinMode(pinLine2, OUTPUT);
  pinMode(pinLine3, OUTPUT);
  pinMode(pinLine4, OUTPUT);
  pinMode(pinLine5, OUTPUT);
  appState = 1;
  brightness = 255;

  // initialize Circuit Playground Express library
  CircuitPlayground.begin();

  // initialize serial communication:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  if (flag == 0) {
    float level = CircuitPlayground.mic.soundPressureLevel(50);
    Serial.println(level);

    if (level > 66)
    {
      Serial.println("flag=" + String(flag) + ", cycleCount=" + String(cycleCount));
      flag = 1;
    }
  }
  else {
    if (cycleCount == 5) {
      Serial.println(9999);
      flag = 0;
    }
  }

  //  Serial.println(appState);
  //  Serial.println(brightness);

  if (flag == 1)
  {
    if (appState == 1) {
      analogWrite(pinLine1, brightness);
      delay(stateDelay);
      appState = 2;
    }
    else if (appState == 2) {
      analogWrite(pinLine2, brightness);
      delay(stateDelay);
      appState = 3;
    }
    else if (appState == 3) {
      analogWrite(pinLine3, brightness);
      delay(stateDelay);
      appState = 4;
    }
    else if (appState == 4) {
      analogWrite(pinLine4, brightness);
      delay(stateDelay);
      appState = 5;
    }
    else if (appState == 5) {
      analogWrite(pinLine5, brightness);
      delay(stateDelay);
      appState = 6;
    }
    else if (appState == 6) {
      fadeLight();
    }
  }
  else {
    analogWrite(pinLine1, 0);
    analogWrite(pinLine2, 0);
    analogWrite(pinLine3, 0);
    analogWrite(pinLine4, 0);
    analogWrite(pinLine5, 0);
    cycleCount = 0;
  }
}

void fadeLight() {
  // set the brightness of each pin
  analogWrite(pinLine1, brightness);
  analogWrite(pinLine2, brightness);
  analogWrite(pinLine3, brightness);
  analogWrite(pinLine4, brightness);
  analogWrite(pinLine5, brightness);

  // reduce brightness until lights go off
  brightness = brightness - fadeAmount;

  // wait for 50 milliseconds to see the dimming effect
  delay(fadeDelay);

  // max brightness and start process again
  if (brightness <= 0) {
    brightness = 0;
    analogWrite(pinLine1, brightness);
    analogWrite(pinLine2, brightness);
    analogWrite(pinLine3, brightness);
    analogWrite(pinLine4, brightness);
    analogWrite(pinLine5, brightness);
    delay(stateDelay);
    brightness = 255;
    appState = 1;
    cycleCount++;
    Serial.println("flag=" + String(flag) + ", cycleCount=" + String(cycleCount));
 }
}

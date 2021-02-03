/**************************************************************************
   Digital Switch Example - 13 switches with LED response and keypresses
   Up to 13 switches can be connected to pins D0-D12.
   Can be used to control the game Patatap: https://patatap.com/
   Adapted from:
   Tactile Interfaces Workshop for IMA Low Res Program - August 14, 2020
   https://gist.github.com/katehartman/9b728a8a34087604a383126a53d1d5f5
   Body-Centric Game Controller Workshop by Social Body Lab
   https://github.com/socialbodylab/Body-Centric-Game-Controllers/tree/master/BodyCentricGameControllers_Experiment1
   Arduino Example code:
   https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardwrite/
   https://www.arduino.cc/en/Reference/KeyboardModifiers
   Keyboard Ascii References:
   http://www.asciitable.com/
**************************************************************************/


#include <Keyboard.h>

const int switchHandle = 2;
const int outputHandle = 13;
const int switchButton = 3;
const int outputButton = 12;
const int switchHinge = 4;
const int outputHinge = 11;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  // set switch pins
  pinMode(switchHandle, INPUT_PULLUP);
  pinMode(switchButton, INPUT_PULLUP);
  pinMode(switchHinge, INPUT_PULLUP);

  // set output pins
  pinMode(outputHandle, OUTPUT);
  pinMode(outputButton, OUTPUT);
  pinMode(outputHinge, OUTPUT);
}

void loop() {
  // fix print out for sensor values vs. key press
  manageLights(switchHandle, outputHandle);
  manageLights(switchButton, outputButton);
  manageLights(switchHinge, outputHinge);

  // delay in between reads for stability
  delay(100);
}

void manageLights(int switchPin, int outputPin) {
  int switchValue = digitalRead(switchPin);
  Serial.println(switchValue);

  if (switchValue == LOW)
  {
    // print the pin number to the Serial Monitor
    Serial.println(switchPin);
    // turn on LED
    digitalWrite(outputPin, HIGH);
    // wait (in milliseconds) to prevent rapidly pressing the key repeatedly
    delay(500);
    // turn off LED
    digitalWrite(outputPin, LOW);
  }
}

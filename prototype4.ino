/*
  Make: Wearable Electronics
  Mapping example
*/

// initialize variables
int lightSensorValue = 0;
int lightSensorPin = A2;
int LEDpin1 = 10;
int LEDpin2 = 1;
int LEDpin3 = 6;
int LEDthreshold = 30;
int mappedLightSensorValue = 0;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // read light sensor pin and store value in a variable:
  lightSensorValue = analogRead(lightSensorPin);

  // map sensor value
  mappedLightSensorValue = map(lightSensorValue, 0, 1023, 0, 255);

  // set analog output accordingly
  if (mappedLightSensorValue > LEDthreshold)
    analogWrite(LEDpin1, mappedLightSensorValue);
  else
    analogWrite(LEDpin1, 0);
  if (mappedLightSensorValue > LEDthreshold*1.5)
    analogWrite(LEDpin2, mappedLightSensorValue);
  else
    analogWrite(LEDpin2, 0);
  if (mappedLightSensorValue > LEDthreshold*2)
    analogWrite(LEDpin3, mappedLightSensorValue);
  else
    analogWrite(LEDpin3, 0);

  // print the sensor and mapped sensor values:
  Serial.print("Light Sensor Value: ");
  Serial.print(lightSensorValue);
  Serial.print(", Mapped Light Sensor Value: ");
  Serial.println(mappedLightSensorValue);

  // delay between readings:
  delay(100);
}

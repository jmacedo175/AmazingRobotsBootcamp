#include "veml6040.h" //https://github.com/thewknd/VEML6040
VEML6040 RGBWSensor;

void setup() {
  Serial.begin(9600);
  if (!RGBWSensor.begin()) {
    Serial.println("not working");
    while (1) {}
  }
  RGBWSensor.setConfiguration(VEML6040_IT_160MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
  Serial.begin(9600);
}

void loop() {
  float r = (float)RGBWSensor.getRed();
  float g = (float)RGBWSensor.getGreen();
  float b = (float)RGBWSensor.getBlue();
  Serial.print(r);
  Serial.print(", ");
  Serial.print(g);
  Serial.print(", ");
  Serial.println(b);
  delay(500);
}


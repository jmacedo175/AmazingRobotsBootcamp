#include <Adafruit_NeoPixel.h>

int neoPixelPin = 0; //pino onde ligámos os leds
int numPixels = 1; //número de leds que temos ligados
int BRIGHTNESS = 50;

Adafruit_NeoPixel strip;
void setup() {
  strip = Adafruit_NeoPixel(numPixels, neoPixelPin, NEO_RGB + NEO_KHZ800);
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);  
}

void loop() {
  // put your main code here, to run repeatedly:
  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.show();
  delay(2000);

  strip.setPixelColor(0, strip.Color(0, 255, 0));
  strip.show();
  delay(2000);

  strip.setPixelColor(0, strip.Color(0, 0, 255));
  strip.show();
  delay(2000);
}

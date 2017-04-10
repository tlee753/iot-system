#include <Adafruit_NeoPixel.h>

#define PIN 4
#define LED_COUNT 31

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  leds.begin();  // Call this to start up the LED strip.
  clearLEDs();   // This function, defined below, turns all LEDs off...
  leds.show();   // ...but the LEDs don't actually update until you call this.

  Serial.begin(9600);
  Serial.println("Program Starting...");
}

void loop() {
  
  int red = 254;
  int green = 127;
  int blue = 1;

  bool redDir = true;
  bool greenDir = true;
  bool blueDir = true;

  while (true) {
    redDir ? red++ : red--;
    greenDir ? green++ : green--;
    blueDir ? blue++ : blue--;

    if (red >= 255 || red <= 0) {
      redDir = !redDir;
    }  
    if (green >= 255 || green <= 0) {
      greenDir = !greenDir;
    }
    if (blue >= 255 || blue <= 0) {
      blueDir = !blueDir;
    }
    
    displayColor(red, green, blue);

    Serial.println(green);
    Serial.println(greenDir);
    delay(50);
  }
  


}

void clearLEDs() {
  for (int i=0; i<LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0);
  }
}

void displayColor(int r, int g, int b) {
  for (int i=0; i < LED_COUNT; i++) {
    leds.setPixelColor(i, r, g, b);
  }
  leds.show();
}


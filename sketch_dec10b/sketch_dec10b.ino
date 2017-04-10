#include <Adafruit_NeoPixel.h>

#define LED_PIN 4
#define BUTTON_PIN 9
#define POT_PIN A0
#define LED_COUNT 31

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // initalize the led array
  leds.begin();

  // clear the leds
  clearLEDs();

  // initialize the button mode
  pinMode(BUTTON_PIN, INPUT);

  // initialize the serial print out
  Serial.begin(9600);
  Serial.println("Program Starting...");
}


void loop() {
  // check potentitometer reading
  int potentiometer = analogRead(POT_PIN);
  int buttonState = digitalRead(BUTTON_PIN);
  
  // color control flow
  if (potentiometer < 50) {
    clearLEDs();
  } else if (potentiometer >= 50 && potentiometer < 100) {
    brightLEDs();
  } else if (potentiometer > 900) {
    randomLEDs();
  } else {
    potentiometer = potentiometer - 100;
    spectrumLEDs(potentiometer, 800);
  }
  delay(250);
}


void displayColor(int r, int g, int b) {
  for (int i=0; i < LED_COUNT; i++) {
    leds.setPixelColor(i, r, g, b);
  }
  leds.show();
}


void clearLEDs() {
  for (int i=0; i<LED_COUNT; i++) {
    leds.setPixelColor(i, 0, 0, 0);
  }
  leds.show();
  Serial.println("Clearing");
}

void brightLEDs() {
  for (int i=0; i<LED_COUNT; i++) {
    leds.setPixelColor(i, 255, 255, 255);
  }
  leds.show();
  Serial.println("Bright");
}


void randomLEDs() {
  for (int i=0; i<LED_COUNT; i++) {
    int red = random(0, 256);
    int green = random(0, 256);
    int blue = random(0, 256);
    leds.setPixelColor(i, red, green, blue);
  }
  leds.show();
  Serial.println("Random");
}


void spectrumLEDs(int input, int maxRange) {
  int thirds = round(maxRange/3);
  int temp;
  int red;
  int green;
  int blue;
  if (input < thirds ) {                  
    temp = (input * 3) / 4;
    red = 256 - temp;
    green = temp;
    blue = 0;
  }
  else if (input < 2*thirds ) {
    temp = ( (input-thirds) * 3) / 4;
    red = 0;
    green = 256 - temp;
    blue = temp;
  }
  else {
    temp = ( (input-(2*thirds)) * 3) / 4;
    red = temp;
    green = 0;
    blue = 256 - temp;
  }
  int rgbArray[] = {red, green, blue};
  //Serial.println(rgbArray[]);

  for (int i=0; i < LED_COUNT; i++) {
    leds.setPixelColor(i, red, green, blue);
  }
  leds.show();
  Serial.println("Spectrum");
}




/*
 * My shot at color spectrum from single input
    float temp = potentiometer - 100; // range between 0 and 800 inclusive
    temp *= 5.12;
    int red = 16 * round(round(temp) % 16);
    int green = 16 * round(round(temp/16) % 16);
    int blue = 16 * round(round(temp/256) % 16);
    displayColor(red, green, blue);
    Serial.println(red);
    Serial.println(green);
    Serial.println(blue);
 */


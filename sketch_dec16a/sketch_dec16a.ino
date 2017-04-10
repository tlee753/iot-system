#include <Adafruit_NeoPixel.h>

#define LED_PIN 4
#define BUTTON_PIN 9
#define POT_PIN A0
#define LED_COUNT 31

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int mode = 0;

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

  // print outs
  Serial.println(potentiometer);

  // switching modes
  if (buttonState) mode++;
  mode = mode % 6; 
  Serial.println(mode);

  // color control flow
  switch (mode) {
    case 0:
      clearLEDs();
      break;
    case 1:
      brightLEDs(potentiometer, 1024);
      break;
    case 2:
      spectrumLEDs(potentiometer, 1024);
      break;
    case 3:
      randomLEDs();
      break;
    case 4:
      for (int i=0; i<LED_COUNT*10; i++) {
        rainbowLEDs(i);
        delay(100);
      }
      break;
    case 5:
      cycloneLEDs(127, 127, 255, 10);
    default:
      displayColor(0, 255, 0);
  }

  // loop corrections
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


void brightLEDs(int input, int maxRange) {
  input = input/(maxRange/256);
  for (int i=0; i<LED_COUNT; i++) {
    leds.setPixelColor(i, input, input, input);
  }
  leds.show();
}


void randomLEDs() {
  for (int i=0; i<LED_COUNT; i++) {
    int red = random(0, 256);
    int green = random(0, 256);
    int blue = random(0, 256);
    leds.setPixelColor(i, red, green, blue);
  }
  leds.show();
}


void spectrumLEDs(int input, int maxRange) {
  // local variables
  int thirds = round(maxRange/3);
  int temp;
  int red;
  int green;
  int blue;

  // color control flow
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

  for (int i=0; i < LED_COUNT; i++) {
    leds.setPixelColor(i, red, green, blue);
  }
  leds.show();
}


void rainbowLEDs(byte startPosition) 
{
  // scaling for the rainbow
  int rainbowScale = 192 / LED_COUNT;
  
  // Next we setup each pixel with the right color
  for (int i=0; i<LED_COUNT; i++) {
    // It'll return a color between red->orange->green->...->violet for 0-191.
    leds.setPixelColor(i, rainbowOrder((rainbowScale * (i + startPosition)) % 192));
  }

  leds.show();
}

// Input a value 0 to 191 to get a color value.
// The colors are a transition red->yellow->green->aqua->blue->fuchsia->red...
uint32_t rainbowOrder(byte position) 
{
  // 6 total zones of color change:
  if (position < 31)  // Red -> Yellow (Red = FF, blue = 0, green goes 00-FF)
  {
    return leds.Color(0xFF, position * 8, 0);
  }
  else if (position < 63)  // Yellow -> Green (Green = FF, blue = 0, red goes FF->00)
  {
    position -= 31;
    return leds.Color(0xFF - position * 8, 0xFF, 0);
  }
  else if (position < 95)  // Green->Aqua (Green = FF, red = 0, blue goes 00->FF)
  {
    position -= 63;
    return leds.Color(0, 0xFF, position * 8);
  }
  else if (position < 127)  // Aqua->Blue (Blue = FF, red = 0, green goes FF->00)
  {
    position -= 95;
    return leds.Color(0, 0xFF - position * 8, 0xFF);
  }
  else if (position < 159)  // Blue->Fuchsia (Blue = FF, green = 0, red goes 00->FF)
  {
    position -= 127;
    return leds.Color(position * 8, 0, 0xFF);
  }
  else  //160 <position< 191   Fuchsia->Red (Red = FF, green = 0, blue goes FF->00)
  {
    position -= 159;
    return leds.Color(0xFF, 0x00, 0xFF - position * 8);
  }
}


void cycloneLEDs(int red, int green, int blue, byte wait)
{
  // weight determines how much lighter the outer "eye" colors are
  const byte weight = 4;

  // Start at closest LED, and move to the outside
  for (int i=0; i<=LED_COUNT-1; i++)
  {
    clearLEDs();
    leds.setPixelColor(i, red, green, blue);  // Set the bright middle eye
    
    // Now set two eyes to each side to get progressively dimmer
    for (int j=1; j<3; j++)
    {
      if (i-j >= 0)
        leds.setPixelColor(i-j, red/(weight*j), green/(weight*j), blue/(weight*j));
      if (i-j <= LED_COUNT)
        leds.setPixelColor(i+j, red/(weight*j), green/(weight*j), blue/(weight*j));
    }
    leds.show();  // Turn the LEDs on
    delay(wait);  // Delay for visibility
  }
  
  // Now we go back to where we came. Do the same thing.
  for (int i=LED_COUNT-2; i>=1; i--)
  {
    clearLEDs();
    leds.setPixelColor(i, red, green, blue);
    for (int j=1; j<3; j++)
    {
      if (i-j >= 0)
        leds.setPixelColor(i-j, red/(weight*j), green/(weight*j), blue/(weight*j));
      if (i-j <= LED_COUNT)
        leds.setPixelColor(i+j, red/(weight*j), green/(weight*j), blue/(weight*j));
      }
    
    leds.show();
    delay(wait);
  } 
}

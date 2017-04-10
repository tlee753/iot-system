
#define BUTTON_PIN 9

int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  Serial.println("Program Starting");

}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState) {
    counter++;
  }
  counter = counter % 5;
  Serial.println(counter);
  delay(1000);
}

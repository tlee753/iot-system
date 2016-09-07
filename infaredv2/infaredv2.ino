/**
 * @author Tyler Lee
 * @version 2.0
 * 
 * Arduino PIR infared/motion sensor detection program which lights onboard LED upon detection
 */

const int LED = 13;                       // define LED ouput pin
const int PIR = 7;                        // define infared/motion sensor input pin

void setup() {
  pinMode(LED, OUTPUT);                   // initalize LED
  pinMode(PIR, INPUT);                    // initialize PIN 7 as infared read
  Serial.begin(9600);                     // begin serial output
  Serial.println("Program Starting");     // test output for monitoring purposes
}

void loop() {
  if (digitalRead(PIR)) {                 // checks for high signal from infared sensor
    digitalWrite(LED, HIGH);              // LED on
    Serial.println("Infared and Motion Detected");
  } else {
    digitalWrite(LED, LOW);               // LED off
    Serial.println("No Infared and Motion Detected");
  }
  
  delay(1000);                            // time delay for stability
}

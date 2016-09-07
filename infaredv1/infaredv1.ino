/**
 * @author Tyler Lee
 * @version 1.0
 * 
 * Arduino PIR infared/motion sensor detection program which lights onboard LED upon detection
 */


void setup() {
  pinMode(13, OUTPUT);                    // initalize LED
  pinMode(7, INPUT);                      // initialize PIN 7 as infared read
  Serial.begin(9600);                     // begin serial output
  Serial.println("Program Starting");     // test output for monitoring purposes
}

void loop() {
  if (digitalRead(7)) {                   // checks for high signal from infared sensor
    digitalWrite(13, HIGH);               // LED on
    Serial.println("Infared and Motion Detected");
  } else {
    digitalWrite(13, LOW);                // LED off
    Serial.println("No Infared and Motion Detected");
  }
  
  delay(1000);                            // time delay for stability
}

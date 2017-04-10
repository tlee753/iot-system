/**
 * @author Tyler Lee
 * @version 2.0
 * 
 * Arduino PIR infared/motion sensor detection program which lights onboard LED upon detection, serial output of analog infared distance sensor, and relay controller
 */

const int PIR = 7;                        // define infared/motion sensor input pin
const int PIR2 = 8;

void setup() {
  pinMode(PIR, INPUT);                    // initialize infared/motion sensor
  pinMode(PIR2, INPUT);                    // initialize 2nd inf/mot sensor
  Serial.begin(9600);                     // begin serial output
  Serial.println("Program Starting");     // test output for monitoring purposes
}

void loop() {
  if (digitalRead(PIR) && digitalRead(PIR2)) {                 // checks for high signal from infared sensor
    Serial.println("Infared and Motion Detected on PIR 1 and 2");
  } else if (digitalRead(PIR)) {
    Serial.println("Infared and Motion Detected on PIR 1");
  } else if (digitalRead(PIR2)) {
    Serial.println("Infared and Motion Detected on PIR 2");
  } else {
    Serial.println("No Infared and Motion Detected");
  }

  delay(500);                            // time delay for stability
}

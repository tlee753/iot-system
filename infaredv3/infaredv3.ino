/**
 * @author Tyler Lee
 * @version 3.0
 * 
 * Arduino PIR infared/motion sensor detection program which lights onboard LED upon detection, serial output of analog infared distance sensor, and relay controller
 */

const int LED = 13;                       // define LED ouput pin
const int PIR = 7;                        // define infared/motion sensor input pin
const int DIS = 14;                        // define distance sensor
const int REL = 6;                        // define relay

bool relayToggle = false;                 // initialize relay toggle

void setup() {
  pinMode(LED, OUTPUT);                   // initalize LED
  pinMode(PIR, INPUT);                    // initialize infared/motion sensor
  pinMode(PIR, INPUT);                    // initialize distance sensor
  pinMode(REL, OUTPUT);                   // initialize relay
  pinMode(15, OUTPUT); 
  Serial.begin(9600);                     // begin serial output
  Serial.println("Program Starting");     // test output for monitoring purposes
}

void loop() {
  for (int i = 0; i < 255; i++) {
    Serial.println(i);
    relayToggle = !relayToggle;
    digitalWrite(LED, relayToggle);
    analogWrite(15, i);
    delay(100);
  }
}

int main() {
    if (digitalRead(PIR)) {                 // checks for high signal from infared sensor
    digitalWrite(LED, HIGH);              // LED on
    Serial.println("Infared and Motion Detected");
  } else {
    digitalWrite(LED, LOW);               // LED off
    Serial.println("No Infared and Motion Detected");
  }
  Serial.print("Distance Sensor Reading: ");
  Serial.println(analogRead(DIS));        // print analog
  // relayToggle = !relayToggle;             // toggle the relay
  // digitalWrite(REL, relayToggle);         // write out the 
  delay(1000);                            // time delay for stability
  return 0;
}


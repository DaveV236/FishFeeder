#include <Wire.h>
#include "RTClib.h" // Adafruit PCF8523 library
#include <Servo.h>

RTC_PCF8523 rtc; // Create an RTC object
Servo myServo;    // Create a servo object

const int relayPin = 10; // The digital pin connected to the relay module's IN pin
const int buttonPin = 2;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Initialize I2C communication

  pinMode(buttonPin, INPUT);

  pinMode(relayPin, OUTPUT); // Set the pin as an output
  digitalWrite(relayPin, LOW); // Initialize the relay to the "off" state

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Uncomment the following line to set the RTC to the compile time
  // rtc.adjust(DateTime(2025, 11, 14, 14, 52, 0)); // (Year, Month, Date, Hour, Minute, Second)

  myServo.attach(9); // Attach the servo to pin 9
  
}

void loop() {
  DateTime now = rtc.now(); // Get current date and time from RTC
  myServo.write(135); // Sends servo to home upon start
 
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
  for (int pos = 45; pos <= 135; pos += 1) { // goes from 45 degrees to 135 degrees
myServo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits 15ms for the servo to reach the position
  }
  }
  // FAN START
  if (now.hour() == 16 && now.minute() == 10 && now.second() == 0) {
  digitalWrite(relayPin, HIGH); // Turn the relay on (or off, depending on module)

}
// FAN STOP
  if (now.hour() == 16 && now.minute() == 10 && now.second() == 15) {  
  digitalWrite(relayPin, LOW);  // Turn the relay off (or on, depending on module)
              
 } 
  // FEEDER ACTUATE
  // Example: Move servo based on time (e.g., at a specific hour)
  if (now.hour() == 16 && now.minute() == 10 && now.second() == 13) {
  for (int pos = 45; pos <= 135; pos += 1) { // goes from 45 degrees to 135 degrees
myServo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits 15ms for the servo to reach the position

}

  delay(1000); // Wait for a second before checking the time again

  myServo.detach();
}}
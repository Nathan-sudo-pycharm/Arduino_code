#include <Servo.h>

Servo myservo;  // Create a servo object

void setup() {
  myservo.attach(9);  // Attach the servo to pin 9
}

void loop() {
  resetServo();  // Call the function to reset the servo to 90 degrees
}

void resetServo() {
  myservo.write(90);  // Set the servo position to 90 degrees
  delay(1000);        // Delay to allow the servo to reach the position
}

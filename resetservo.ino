
#include <Servo.h>

#define servoPin A5 // Servo pin

Servo myservo; // Create a servo object

void setup() {
  Serial.begin(9600); // Initialize serial communication
  myservo.attach(servoPin); // Attach the servo to pin A5
}

void loop() {
  resetServo(); // Call the function to reset the servo to 90 degrees
}

void resetServo() {
  myservo.write(90); // Set the servo position to 90 degrees
  Serial.print("Servo position: ");
  Serial.println(myservo.read()); // Print the current position of the servo
  delay(600); // Delay to allow the servo to reach the position
}
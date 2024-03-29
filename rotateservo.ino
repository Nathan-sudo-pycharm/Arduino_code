// code to rotate servo  motor to 90 degrees for 5 secs  wait for 2 secs then go 0degrees, then 180 degrees
#include <Servo.h>

#define servoPin A5 // Servo pin

Servo myservo; // Create a servo object

void setup() {
  myservo.attach(servoPin); // Attach the servo to pin A5
}

void loop() {
  // Move to 90 degrees
  myservo.write(90);
  delay(5000); // 5 seconds delay
  delay(2000); // 2 seconds delay

  // Move to 0 degrees
  myservo.write(0);
  delay(5000); // 5 seconds delay
  delay(2000); // 2 seconds delay

  // Move to 180 degrees
  myservo.write(180);
  delay(5000); // 5 seconds delay
  delay(2000); // 2 seconds delay

  // Move back to 90 degrees
  myservo.write(90);
  delay(3000); // 3 seconds delay
}


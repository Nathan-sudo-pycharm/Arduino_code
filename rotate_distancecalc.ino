/*
This code sets up a servo motor and ultrasonic sensor, and motor drivers to control a robotic vehicle. 
It rotates the servo to three different angles (90, 0, and 180 degrees) and measures the distance using the ultrasonic sensor at each angle.
 The distances are then printed to the serial monitor. Adjustments can be made to suit specific hardware configurations and application requirements.
*/
#include <Servo.h>

#define echoPin A2 // Echo pin for ultrasonic sensor
#define trigPin A3 // Trigger pin for ultrasonic sensor
#define servoPin A5 // Servo pin



int Set = 15; // Threshold for sensor readings
int distance_L, distance_F, distance_R; // Variables to store distance readings

Servo myservo; // Create a servo object

void setup() {
  Serial.begin(9600); // Initialize serial communication
  myservo.attach(servoPin); // Attach the servo to pin A5

  // Set pin modes
  pinMode(R_S, INPUT); // Right IR sensor pin
  pinMode(L_S, INPUT); // Left IR sensor pin
  pinMode(echoPin, INPUT); // Ultrasonic sensor Echo pin
  pinMode(trigPin, OUTPUT); // Ultrasonic sensor Trigger pin
  pinMode(enA, OUTPUT); // L298 Pin enA
  pinMode(in1, OUTPUT); // L298 Pin in1
  pinMode(in2, OUTPUT); // L298 Pin in2
  pinMode(in3, OUTPUT); // L298 Pin in3
  pinMode(in4, OUTPUT); // L298 Pin in4
  pinMode(enB, OUTPUT); // L298 Pin enB

  // Initialize motor speeds
  analogWrite(enA, 200); // Motor1 speed
  analogWrite(enB, 200); // Motor2 speed

  // Sweep the servo from 70 to 140 degrees in steps of 5 degrees
  for (int angle = 70; angle <= 140; angle += 5) {
    servoPulse(servoPin, angle);
  }
  // Sweep the servo from 140 to 0 degrees in steps of -5 degrees
  for (int angle = 140; angle >= 0; angle -= 5) {
    servoPulse(servoPin, angle);
  }
  // Sweep the servo from 0 to 70 degrees in steps of 5 degrees
  for (int angle = 0; angle <= 70; angle += 5) {
    servoPulse(servoPin, angle);
  }

  // Read initial distance from ultrasonic sensor
  distance_F = Ultrasonic_read();
  delay(500); // Delay for stability
}

void loop() {
  rotateAndMeasure(90); // Rotate to 90 degrees and measure distance
  delay(2000); // Delay for 2 seconds

  rotateAndMeasure(0); // Rotate to 0 degrees and measure distance
  delay(2000); // Delay for 2 seconds

  rotateAndMeasure(180); // Rotate to 180 degrees and measure distance
  delay(2000); // Delay for 2 seconds
}

// Function to rotate the servo to a specified angle and measure distance
void rotateAndMeasure(int angle) {
  myservo.write(angle); // Rotate the servo to the specified angle
  delay(1000); // Delay for stabilization of servo movement
  int distance = Ultrasonic_read(); // Measure distance at the specified angle
  Serial.print("Distance at ");
  Serial.print(angle);
  Serial.print(" degrees: ");
  Serial.print(distance);
  Serial.println(" cm");
}

// Function to generate servo pulse
void servoPulse(int pin, int angle) {
  int pwm = (angle * 11) + 500; // Convert angle to microseconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(pin, LOW);
  delay(50); // Refresh cycle of servo
}

// Function to measure distance using ultrasonic sensor
long Ultrasonic_read() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  long time = pulseIn(echoPin, HIGH);
  return time / 29 / 2; // Calculate and return distance in centimeters
}

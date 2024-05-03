#include <AFMotor.h>  // Include the AFMotor library for controlling the motors
#include <NewPing.h>  // Include the NewPing library for ultrasonic sensor
#include <Servo.h>    // Include the Servo library for controlling the servo motor

#define TRIG_PIN A0    // Define the trigger pin for the ultrasonic sensor
#define ECHO_PIN A1    // Define the echo pin for the ultrasonic sensor
#define MAX_DISTANCE 200  // Define the maximum distance for the ultrasonic sensor
#define MAX_SPEED 190     // Set the maximum speed of the DC motors
#define MAX_SPEED_OFFSET 20 // Set the maximum speed offset

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // Create a NewPing object for the ultrasonic sensor

// Create AF_DCMotor objects for each motor
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

Servo myservo;   // Create a Servo object for the servo motor

boolean goesForward=false; // Variable to track the direction of movement
int distance = 100;  // Variable to store the distance measured by the ultrasonic sensor
int speedSet = 0;    // Variable to set the speed of the motors
unsigned long startTime; // Variable to store the start time

void setup() {
  myservo.attach(10);  // Attach the servo motor to pin 10  
  myservo.write(115);  // Set the initial position of the servo motor
  delay(2000); // Wait for 2 seconds
  distance = readPing();  // Read the initial distance from the ultrasonic sensor
  delay(100);  // Delay for stabilization
  distance = readPing();  // Read the distance again
  delay(100);  // Delay for stabilization
  distance = readPing();  // Read the distance again
  delay(100);  // Delay for stabilization
  distance = readPing();  // Read the distance again
  delay(100);  // Delay for stabilization
  startTime = millis(); // Record the start time
}

void loop() {
  int distanceR = 0;  // Variable to store the distance measured by the right sensor
  int distanceL =  0; // Variable to store the distance measured by the left sensor
  delay(40);  // Delay for stabilization
  if (millis() - startTime < 60000) { // Check if 1 minute has not elapsed
    if(distance<=17) { // If obstacle detected within 17 cm
      moveStop(); // Stop the robot
      delay(100);  // Delay for stabilization
      moveBackward(); // Move backward
      delay(300);  // Delay for a short duration
      moveStop(); // Stop the robot
      delay(200);  // Delay for stabilization
      distanceR = lookRight(); // Measure distance to the right
      delay(200);  // Delay for stabilization
      distanceL = lookLeft(); // Measure distance to the left
      delay(200);  // Delay for stabilization
      if(distanceR>=distanceL) { // If distance to right is greater than or equal to distance to left
        turnRight(); // Turn right
        moveStop(); // Stop the robot
      } else { // Otherwise
        turnLeft(); // Turn left
        moveStop(); // Stop the robot
      }
    } else { // If no obstacle detected
      moveForward(); // Move forward
    }
    distance = readPing(); // Read the distance from the ultrasonic sensor
  } else { // If 1 minute has elapsed
    moveStop(); // Stop the robot
  }
}

// Function to measure distance to the right
int lookRight() {
  myservo.write(0); // Rotate the servo to the right
  delay(500);  // Delay for servo movement
  int distance = readPing(); // Read the distance from the ultrasonic sensor
  delay(100);  // Delay for stabilization
  myservo.write(115); // Reset the servo to the center position
  return distance; // Return the measured distance
}

// Function to measure distance to the left
int lookLeft() {
  myservo.write(180); // Rotate the servo to the left
  delay(500);  // Delay for servo movement
  int distance = readPing(); // Read the distance from the ultrasonic sensor
  delay(100);  // Delay for stabilization
  myservo.write(115); // Reset the servo to the center position
  return distance; // Return the measured distance
}

// Function to read distance from the ultrasonic sensor
int readPing() { 
  delay(70);  // Delay for sensor stabilization
  int cm = sonar.ping_cm(); // Measure distance in centimeters
  if(cm == 0) { // If distance is zero (no obstacle detected)
    cm = 200; // Set distance to a high value
  }
  return cm; // Return the measured distance
}

// Function to stop the robot
void moveStop() {
  motor1.run(RELEASE); // Stop motor 1
  motor2.run(RELEASE); // Stop motor 2
  motor3.run(RELEASE); // Stop motor 3
  motor4.run(RELEASE); // Stop motor 4
} 

// Function to move the robot forward
void moveForward() {
  if(!goesForward) { // If not already moving forward
    goesForward = true; // Set direction to forward
    motor1.run(FORWARD); // Move motor 1 forward
    motor2.run(FORWARD); // Move motor 2 forward
    motor3.run(FORWARD); // Move motor 3 forward
    motor4.run(FORWARD); // Move motor 4 forward
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) { // Gradually increase speed
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

// Function to move the robot backward
void moveBackward() {
  goesForward = false; // Set direction to backward
  motor1.run(BACKWARD); // Move motor 1 backward
  motor2.run(BACKWARD); // Move motor 2 backward
  motor3.run(BACKWARD); // Move motor 3 backward
  motor4.run(BACKWARD); // Move motor 4 backward
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) { // Gradually increase speed
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  

// Function to turn the robot right
void turnRight() {
  motor1.run(FORWARD); // Move motor 1 forward
  motor2.run(FORWARD); // Move motor 2 forward
  motor3.run(BACKWARD); // Move motor 3 backward
  motor4.run(BACKWARD); // Move motor 4 backward
  delay(500); // Delay for turning
  motor1.run(FORWARD); // Move motor 1 forward
  motor2.run(FORWARD); // Move motor 2 forward
  motor3.run(FORWARD); // Move motor 3 forward
  motor4.run(FORWARD); // Move motor 4 forward
} 
 
// Function to turn the robot left
void turnLeft() {
  motor1.run(BACKWARD); // Move motor 1 backward
  motor2.run(BACKWARD); // Move motor 2 backward
  motor3.run(FORWARD); // Move motor 3 forward
  motor4.run(FORWARD); // Move motor 4 forward
  delay(500); // Delay for turning
  motor1.run(FORWARD); // Move motor 1 forward
  motor2.run(FORWARD); // Move motor 2 forward
  motor3.run(FORWARD); // Move motor 3 forward
  motor4.run(FORWARD); // Move motor 4 forward
}


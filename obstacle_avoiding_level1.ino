//if obstacle is detected in front , then the car stops. If no obstacle inn front , then the car moves forward
#define enA 10 // Enable1 L298 Pin enA
#define in1 9 // Motor1 L298 Pin in1
#define in2 8 // Motor1 L298 Pin in2
#define in3 7 // Motor2 L298 Pin in3
#define in4 6 // Motor2 L298 Pin in4
#define enB 5 // Enable2 L298 Pin enB

#define echoPin A2 // Echo pin for ultrasonic sensor
#define trigPin A3 // Trigger pin for ultrasonic sensor

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  if (isObstacleInFront()) {
    // Stop motors if obstacle detected
    stopMotors();
  } else {
    // Move forward if no obstacle detected
    moveForward();
  }
}

bool isObstacleInFront() {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Adjust this threshold as needed
  if (distance <= 15) {
    return true; // Obstacle detected
  } else {
    return false; // No obstacle detected
  }
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 200); // Adjust speed as needed
  analogWrite(enB, 200); // Adjust speed as needed
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

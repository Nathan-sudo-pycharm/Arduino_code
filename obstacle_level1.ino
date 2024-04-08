#define enA 10    // Enable1 L298 Pin enA 
#define in1 9     // Motor1  L298 Pin in1 
#define in2 8     // Motor1  L298 Pin in1 
#define in3 7     // Motor2  L298 Pin in1 
#define in4 6     // Motor2  L298 Pin in1 
#define enB 5     // Enable2 L298 Pin enB 

#define echo A2   // Echo pin
#define trigger A3  // Trigger pin

#define obstacleDistanceThreshold 15  // Minimum distance in cm

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Set the motor direction to move forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Set the motor speed
  analogWrite(enA, 100); // Adjust the speed as needed (0 to 255)
  analogWrite(enB, 100); // Adjust the speed as needed (0 to 255)
}

void loop() {
  // Measure distance using ultrasonic sensor
  long duration, distance;
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  // Check if obstacle is closer than threshold distance
  if (distance < obstacleDistanceThreshold) {
    // Stop the car if obstacle detected
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } else {
    // Move the car forward if no obstacle
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

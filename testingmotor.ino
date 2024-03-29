// Code that makes sure the car moves forward for 5 secs and then stops    Delay means to wait and it is calculated in miliseconds [2000 is 2 seconds]


#define enA 10 // Enable1 L298 Pin enA
#define in1 9 // Motor1 L298 Pin in1
#define in2 8 // Motor1 L298 Pin in2
#define in3 7 // Motor2 L298 Pin in3
#define in4 6 // Motor2 L298 Pin in4
#define enB 5 // Enable2 L298 Pin enB

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
}

void loop() {
  // Spin all motors forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 200); // Adjust speed as needed
  analogWrite(enB, 200); // Adjust speed as needed
  delay(5000); // Move forward for 5 seconds
  stopMotors();
  delay(3000); // Stop for 3 seconds
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

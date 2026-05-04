#include <Servo.h> // Library for controlling the servo motor
// --- PIN DEFINITIONS ---
// Define sensor and actuator pins
const int trigPin = 9;
const int echoPin = 8;
const int pirPin = 2;
const int ldrPin = A0;
const int buzzer = 7; // Buzzer pin (moved to avoid startup noise)
const int redLED = 12; // Alarm indicator LED
const int nightLED = 11; // Night mode indicator LED
Servo myServo; // Servo motor object
// --- FSM STATES ---
// Define system states for the Finite State Machine
const int PATROL_MODE = 0; // Default monitoring mode
const int OBSTACLE_MODE = 1; // Obstacle detected
const int INTRUDER_MODE = 2; // Motion detected (alarm)
const int NIGHT_MODE = 3; // Low light condition
int currentState = PATROL_MODE; // Initial system state
void setup() {
// --- INITIALIZE OUTPUTS SAFELY ---
pinMode(buzzer, OUTPUT);
digitalWrite(buzzer, LOW); // Ensure buzzer is OFF at startup
pinMode(redLED, OUTPUT);
digitalWrite(redLED, LOW); // Turn off alarm LED
pinMode(nightLED, OUTPUT);
digitalWrite(nightLED, LOW); // Turn off night LED
// --- SENSOR PIN SETUP ---
pinMode(trigPin, OUTPUT); // Ultrasonic trigger
pinMode(echoPin, INPUT); // Ultrasonic echo
pinMode(pirPin, INPUT); // PIR motion sensor
// --- SERVO INITIALIZATION ---
myServo.attach(10);
myServo.write(90); // Set servo to neutral (center) position
Serial.begin(9600); // Start serial communication for debugging
}
void loop() {
// --- SENSE: Read data from sensors ---
long distance = readDistance(); // Measure distance using ultrasonic sensor
int motion = digitalRead(pirPin); // Detect motion (PIR sensor)
int lightValue = analogRead(ldrPin); // Read ambient light level
// --- DECIDE: Priority-based decision making ---
// Priority: Intruder > Obstacle > Night > Patrol
if (motion == HIGH) {
currentState = INTRUDER_MODE; // Highest priority: motion detected
}
else if (distance > 0 && distance < 20) {
currentState = OBSTACLE_MODE; // Obstacle detected within 20 cm
}
else if (lightValue < 400) {
currentState = NIGHT_MODE; // Low light condition
}
else {
currentState = PATROL_MODE; // Default behavior
}
// --- ACT: Execute behavior based on state ---
applyBehavior(currentState);
delay(50); // Small delay for stability and responsiveness
}
// --- ULTRASONIC DISTANCE MEASUREMENT FUNCTION ---
long readDistance() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH); // Send ultrasonic pulse
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
long duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30 ms
if (duration == 0) return 100; // If no response, assume no obstacle nearby
return duration * 0.034 / 2; // Convert time to distance (cm)
}
// --- FSM BEHAVIOR FUNCTION ---
void applyBehavior(int state) {
switch(state) {
case INTRUDER_MODE:
Serial.println("STATE: INTRUDER ALERT!");
digitalWrite(buzzer, HIGH); // Activate buzzer
digitalWrite(redLED, HIGH); // Turn on alarm LED
digitalWrite(nightLED, LOW);
myServo.write(90); // Stop movement (alert state)
break;
case OBSTACLE_MODE:
Serial.println("STATE: OBSTACLE AVOIDANCE");
digitalWrite(buzzer, LOW);
digitalWrite(redLED, LOW);
myServo.write(0); // Change direction to avoid obstacle
break;
case NIGHT_MODE:
Serial.println("STATE: NIGHT MODE");
digitalWrite(nightLED, HIGH); // Turn on night LED
digitalWrite(redLED, LOW);
digitalWrite(buzzer, LOW);
myServo.write(90);
break;
case PATROL_MODE:
Serial.println("STATE: PATROL");
digitalWrite(redLED, LOW);
digitalWrite(nightLED, LOW);
digitalWrite(buzzer, LOW);
myServo.write(90); // Neutral position (idle monitoring)
break;
}
}
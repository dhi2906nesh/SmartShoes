// Define the buzzer pins for each sensor
const int buzzerPin1 = 8;
const int buzzerPin2 = 9
// Define the ultrasonic sensor pins
const int trigPin1 = 10; // Trigger pin for sensor 1
const int echoPin1 = 11; // Echo pin for sensor 1
const int trigPin2 = 12; // Trigger pin for sensor 2
const int echoPin2 = 13; // Echo pin for sensor 2

// Define the maximum distance for object detection (in centimeters)
const int maxDistance = 10; // You can adjust this value as needed

void setup() {
  // Set the buzzer pins as OUTPUT
  pinMode(buzzerPin1, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);

  // Set the trigger pins as OUTPUT and echo pins as INPUT
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Measure the distance for sensor 1
  int distance1 = measureDistance(trigPin1, echoPin1);
  playBuzzer(distance1, buzzerPin1);

  // Measure the distance for sensor 2
  int distance2 = measureDistance(trigPin2, echoPin2);
  playBuzzer(distance2, buzzerPin2);
}

int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration / 29 / 2;

  return distance;
}

void playBuzzer(int distance, int buzzerPin) {
  if (distance < maxDistance) {
    // Object detected, play a custom tune for the buzzer
    switch (buzzerPin) {
      case buzzerPin1:
        playTune1(buzzerPin);
        break;
      case buzzerPin2:
        playTune2(buzzerPin);
        break;
    }
  } else {
    // No object detected, turn off the buzzer
    noTone(buzzerPin);
  }
  // Add a delay to avoid continuous sound
  delay(200);
}

// Define custom tunes for each buzzer
void playTune1(int buzzerPin) {
  tone(buzzerPin, 800); // Tune 1: Play a moderate-pitched tone (800 Hz)
  delay(150);           // Duration of the tune in milliseconds
  noTone(buzzerPin);    // Turn off the buzzer
}

void playTune2(int buzzerPin) {
    // Play the horn sound
  for (int i = 200; i <= 1000; i += 50) {
    tone(buzzerPin, i);
    delay(50);
  }
  
  noTone(buzzerPin); // Turn off the buzzer
  
  delay(500); // Pause before playing the horn sound again
}
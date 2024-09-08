#define AE1 5   // Encoder pin1 for motor A
#define AE2 18  // Encoder pin2 for motor A

const int motorA1Pin = 25;  // Connect to A1 on DRV8833
const int motorA2Pin = 26;  // Connect to A2 on DRV8833

volatile int encoderCount = 0; // count encoder

void setup() {
  Serial.begin(9600);
  // Initialize motor control pins
  pinMode(motorA1Pin, OUTPUT);
  pinMode(motorA2Pin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(AE1), updateEncoders, RISING);
}

void loop() {
  // Move motor forward
  digitalWrite(motorA1Pin, HIGH);
  digitalWrite(motorA2Pin, LOW);
  delay(2000);  // Run motor for 2 seconds

  // Stop motor
  digitalWrite(motorA1Pin, LOW);
  digitalWrite(motorA2Pin, LOW);
  delay(1000);  // Stop for 1 second

  // Move motor backward
  digitalWrite(motorA1Pin, LOW);
  digitalWrite(motorA2Pin, HIGH);
  delay(2000);  // Run motor for 2 seconds

  // Stop motor again
  digitalWrite(motorA1Pin, LOW);
  digitalWrite(motorA2Pin, LOW);
  delay(1000);  // Stop for 1 second

  Serial.print("encoderCount=");
  Serial.println (encoderCount);
}

void updateEncoders() {
  // Read encoder states
  int stateA = digitalRead(AE1);
  int stateB = digitalRead(AE2);
 
  // Update encoder counts
  if (stateA > stateB) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}

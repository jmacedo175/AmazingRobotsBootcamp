#include "Wire.h"

#define AIN1 33  // ESP32 Pin D13 to TB6612FNG Pin AIN1
#define AIN2 32  // ESP32 Pin D14 to TB6612FNG Pin AIN2
#define BIN1 26  // ESP32 Pin D12 to TB6612FNG Pin BIN1
#define BIN2 25  // ESP32 Pin D27 to TB6612FNG Pin BIN2
#define BE1 5    //Encoder pin1 for motor A
#define BE2 18   //Encoder pin2 for motor A
#define AE2 19   //Encoder pin1 for motor B
#define AE1 17   //Encoder pin2 for motor B

// odometry //
volatile int encoderCount_Left = 0;
volatile int encoderCount_Right = 0;
unsigned long prevTime = 0;
float elapsedTime;

const float wheelDiameter = 6.0;  // in cm
const float wheelCircumference = PI * wheelDiameter;
const float distanceBetweenWheels = 15;  // in cm
const int gearboxRatio = 210;  //motor rotations per one rotation of the wheel
const int pulsesPerRevolution = 7; // Number of pulses per rotation of the motor

float leftWheelSpeed=0;
float rightWheelSpeed=0;
float robotX = 0.0;      // Initial X coordinate
float robotY = 0.0;      // Initial Y coordinate
float robotTheta = 0.0;  // Initial orientation (in radians)

int leftPWM=50;
int rightPWM=50;
float wheelSpeed = 3;
bool moving = false;

TaskHandle_t odometryTask;


//Line Sensors
int nLineSensors = 5;
int lineSensorPins[] = {36,39,34,35,27}; //from left to right

int lineSensors[5];
TaskHandle_t lineSensorTask;


void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Set encoder pins as inputs
  pinMode(AE1, INPUT_PULLUP);
  pinMode(AE2, INPUT_PULLUP);
  pinMode(BE1, INPUT_PULLUP);
  pinMode(BE2, INPUT_PULLUP);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);


  // Attach interrupt handlers
  attachInterrupt(digitalPinToInterrupt(AE1), updateEncodersLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(BE1), updateEncodersRight, RISING);

  initLineSensors();

  xTaskCreate(computeOdometry, "TaskOdometry", 10000, NULL, 1, &odometryTask);
  xTaskCreate(readLineSensors, "TaskLineSensors", 10000, NULL, 1, &lineSensorTask);

}


void loop() {
  //Serial.print(encoderCount_Left); Serial.print(" "); Serial.println(encoderCount_Right);
  /*moveFront(10);
  delay(500);
  rotate(-PI/8);
  delay(500);*/

  Serial.print(lineSensors[0]); Serial.print(" ");Serial.print(lineSensors[1]); Serial.print(" ");Serial.print(lineSensors[2]); Serial.print(" ");Serial.print(lineSensors[3]); Serial.print(" ");Serial.println(lineSensors[4]);
  delay(500);
}


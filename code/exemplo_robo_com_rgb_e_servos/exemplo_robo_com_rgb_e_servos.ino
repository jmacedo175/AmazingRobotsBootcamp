#include "Wire.h"
#include "veml6040.h" //https://github.com/thewknd/VEML6040
#include <ESP32Servo.h> 


#define greenServoPin 2 
#define orangeServoPin 4

#define BIN1 33  // ESP32 Pin D13 to TB6612FNG Pin AIN1
#define BIN2 32  // ESP32 Pin D14 to TB6612FNG Pin AIN2
#define AIN1 26  // ESP32 Pin D12 to TB6612FNG Pin BIN1
#define AIN2 25  // ESP32 Pin D27 to TB6612FNG Pin BIN2
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
float robotX = 0.0;      // Initial X coordinate (in cm)
float robotY = 0.0;      // Initial Y coordinate (in cm)
float robotTheta = 0.0;  // Initial orientation (in radians)

float movementThreshold = 0.25; //linear movement threshold
float rotationThreshold = 0.05; //rotation over the robot's axis threshold

int leftPWM=50;
int rightPWM=50;
float wheelSpeed = 3; //(cm/s)
bool moving = false;

TaskHandle_t odometryTask;


//Line Sensors
int nLineSensors = 5;
int lineSensorPins[] = {27,35,34,39,36};//{36,39,34,35,27}; //from left to right

int lineSensors[5];
TaskHandle_t lineSensorTask;

VEML6040 RGBWSensor;
float color[3];
TaskHandle_t rgbSensorTask;

Servo greenServo;  
Servo orangeServo;  


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
  initRGBSensors();
  initServos();

  xTaskCreate(computeOdometry, "TaskOdometry", 10000, NULL, 1, &odometryTask);
  xTaskCreate(readLineSensors, "TaskLineSensors", 10000, NULL, 1, &lineSensorTask);
  xTaskCreate(readRGBSensors, "TaskRGBSensors", 10000, NULL, 1, &rgbSensorTask);

}


void loop() {
  
  //--------inspect state variables-------
    //print the values of the line sensors (from leftmost to rightmost)
    //Serial.print(lineSensors[0]); Serial.print(" ");Serial.print(lineSensors[1]); Serial.print(" ");Serial.print(lineSensors[2]); Serial.print(" ");Serial.print(lineSensors[3]); Serial.print(" ");Serial.println(lineSensors[4]);  

    //print the RGB values detected by the RGB sensor
    /*Serial.print(color[0]); Serial.print(", "); Serial.print(color[1]); Serial.print(", "); Serial.println(color[2]);*/

    //print the wheel speeds
    //Serial.print(leftWheelSpeed); Serial.print(" "); Serial.println(rightWheelSpeed);

    //print the robot pose
    //Serial.print(robotX); Serial.print(", "); Serial.print(robotY); Serial.print(", "); Serial.println(robotTheta);


  //-----------actions--------------------
    //moveFront(10); //move front x cm
    //rotate(-PI/2); //rotate x radians (negative values rotate to the left)
    //move(leftPWM, rightPWM); //move with automatically adjusted PWM values. Both positive values move the robot front. Both negative values move the robot back. Negative left values and positive right values rotate the robot to the left and the other way around rotate it to the right.


    //greenServoUP(); //raise green flag
    //orangeServoUP(); //raise orange flag
    //greenServoDown(); //lower green flag
    //orangeServoDown(); //lower orange flag

  

  //Serial.print(lineSensors[0]); Serial.print(" ");Serial.print(lineSensors[1]); Serial.print(" ");Serial.print(lineSensors[2]); Serial.print(" ");Serial.print(lineSensors[3]); Serial.print(" ");Serial.println(lineSensors[4]);

  delay(500);
}


// Function to update encoder counts
void updateEncodersLeft() {
  // Read encoder states
  int stateA = digitalRead(AE1);
  int stateB = digitalRead(AE2);
 
  // Update encoder counts
  if (stateA > stateB) {
    encoderCount_Left++;
  } else {
    encoderCount_Left--;
  }
}

// Function to update encoder counts
void updateEncodersRight() {
  // Read encoder states
  int stateA = digitalRead(BE1);
  int stateB = digitalRead(BE2);
 
  // Update encoder counts
  if (stateA > stateB) {
    encoderCount_Right++;
  } else {
    encoderCount_Right--;
  }
}


// Function to compute robot's position and orientation
void computePosition() {
  unsigned long currentTime = millis();
  elapsedTime = (currentTime - prevTime)*1.0/1000;

  // Calculate distance traveled by each wheel considering gearbox ratio and encoder resolution
  float rotation_Left = encoderCount_Left * 1.0 / (gearboxRatio*pulsesPerRevolution);
  float distance_Left = rotation_Left*wheelCircumference; //(encoderCount_Left * wheelCircumference * gearboxRatio) / (pulsesPerRevolution *1.0);
  
  float rotation_Right = encoderCount_Right * 1.0 / (gearboxRatio*pulsesPerRevolution);
  float distance_Right = rotation_Right * wheelCircumference; //(encoderCount_Right * wheelCircumference * gearboxRatio) / (pulsesPerRevolution*1.0);

  leftWheelSpeed = distance_Left/elapsedTime;
  rightWheelSpeed = distance_Right/elapsedTime;

    // Calculate total distance traveled and change in orientation
    float totalDistance = (distance_Left + distance_Right) / 2.0;
    float deltaTheta = (distance_Right - distance_Left) / distanceBetweenWheels;

    // Update robot's position and orientation
    robotTheta += deltaTheta;
    robotX += totalDistance * cos(robotTheta);
    robotY += totalDistance * sin(robotTheta);

    // Reset encoder counts and update time
    encoderCount_Left = 0;
    encoderCount_Right = 0;
    prevTime = currentTime;
}

void calibrateWheels(float desiredSpeed){
  if(abs(leftWheelSpeed)>wheelSpeed) leftPWM--;
  else if (abs(leftWheelSpeed)<wheelSpeed) leftPWM++;
  leftPWM = max(min(255, leftPWM),0);

  if(abs(rightWheelSpeed)>wheelSpeed) rightPWM--;
  else if (abs(rightWheelSpeed)<wheelSpeed) rightPWM++;
  rightPWM = max(min(255, rightPWM),0);
}

void computeOdometry(void* params){
  while(true){
    computePosition();
    if (moving) calibrateWheels(wheelSpeed);
    delay(50);
  }
}
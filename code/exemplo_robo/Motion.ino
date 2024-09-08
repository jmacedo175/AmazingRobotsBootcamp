void leftWheelFront(int pwm){
  analogWrite(BIN1,pwm); 
  analogWrite(BIN2,LOW);
}

void rightWheelFront(int pwm){
  analogWrite(AIN1,pwm); 
  analogWrite(AIN2,LOW);
}

void leftWheelBack(int pwm){
  analogWrite(BIN2,pwm); 
  analogWrite(BIN1,LOW);
}

void rightWheelBack(int pwm){
  analogWrite(AIN2,pwm); 
  analogWrite(AIN1,LOW);
}


void moveFront(float dist){
    float initX = robotX;
    float initY = robotY;

    float thresh = 0.5;
    float currDist = 0;

    while(currDist<(dist-thresh)){
      move(leftPWM, rightPWM);
      currDist = sqrt(pow(initX-robotX,2) + pow(initY-robotY,2));
            delay(100);
    }

    move(0,0);
}

void rotate(float angle){
  float rotated = 0;
  bool left = (angle>0);
  angle = abs(angle);
  float initAngle = robotTheta;
  float thresh = 0.05;

  while(rotated<angle-thresh){
    noInterrupts();
    rotated = abs(robotTheta - initAngle);
    interrupts();
    if (rotated>PI) rotated = 2*PI - rotated;

    if(left) move(leftPWM, -rightPWM);
    else move(-leftPWM, rightPWM);
    delay(50);

  }
  move(0,0);

}

void move(int pwmEsq, int pwmDir){
  moving = (pwmEsq!=0 || pwmDir!=0);
  if (pwmEsq >= 0) leftWheelFront(pwmEsq);
  else leftWheelBack(-pwmEsq);

  if (pwmDir >=0) rightWheelFront(pwmDir);
  else rightWheelBack(-pwmDir);
}




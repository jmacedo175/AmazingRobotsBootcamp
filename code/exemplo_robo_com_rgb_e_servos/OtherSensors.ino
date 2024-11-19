void initLineSensors(){
  for (int i =0;i<nLineSensors;i++){
    pinMode(lineSensorPins[i], INPUT);
  }
}

void readLineSensors(void* params){
  while(true){
    for (int i =0;i<nLineSensors;i++){
      lineSensors[i] = analogRead(lineSensorPins[i]);
    }
    delay(50);
  }
}




void initRGBSensors() {
  if (!RGBWSensor.begin()) {
    Serial.println("not working");
    while (1) {}
  }
  RGBWSensor.setConfiguration(VEML6040_IT_160MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
}

void readRGBSensors(void* params) {
  while(true){
    color[0] = (float)RGBWSensor.getRed();
    color[1] = (float)RGBWSensor.getGreen();
    color[2] = (float)RGBWSensor.getBlue();


    delay(50);
  }

}


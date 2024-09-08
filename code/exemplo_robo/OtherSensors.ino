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
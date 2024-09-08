#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);

  // Espera até o porto esteja disponível
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  // A função rangingTest ativa o sensor para medir a distância de um objeto à frente dele.
  // O resultado é armazenado na variável measure.
  lox.rangingTest(&measure, false);  // Ao passar false, a função executa a medição normalmente,
                                     //sem imprimir informações extras na saída serial.

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distância (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" fora do alcance ");
  }
  delay(100);
}

#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int sensorPin = 35; //IR
#define VOLTAGE 3.3 //IR
#define MIN_ANALOG 0 //IR
#define MAX_ANALOG 4096.0 //IR

const int trigPin = 5; //ultrasonico
const int echoPin = 18; //ultrasonico
#define SOUND_SPEED 0.034 //Definir a velocidade do som em cms por segundos

void setup() {
  Serial.begin(9600); // Início da Comunicação em Série

  // Espera até o porto esteja disponível 
  while (! Serial) {
    delay(1);
  }
  if (!lox.begin()) {//VL53
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  pinMode(sensorPin, INPUT); //IR

  pinMode(trigPin, OUTPUT); //ultrasonico
  pinMode(echoPin, INPUT); //ultrasonico

}

void loop() {

  IR_loop();
  delay(5000);

  ultrasonico_loop();
  delay(5000);

  VL53_loop();
  delay(5000);
}

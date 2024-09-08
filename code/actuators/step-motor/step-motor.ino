  #include <AccelStepper.h>  //https://github.com/swissbyte/AccelStepper
#define motorInterfaceType 4 /

AccelStepper stepper = AccelStepper(motorInterfaceType, 25, 27, 26, 14);  // IN1, IN3, IN2, IN4

void setup() {
  stepper.setMaxSpeed(1000);     // Definir velocidade máxima (passos por segundo)
  stepper.setAcceleration(500);  // Definir aceleração (passos por segundo^2)
  Serial.begin(9600);
}

void loop() {
  // andar para a frente
  stepper.moveTo(2038);

  while (stepper.distanceToGo() != 0) {
    stepper.run();  // Esta função deve ser chamada até o movimento estar completo
  }

  delay(1000);

  // andar para trás
  stepper.moveTo(-2038);
  while (stepper.distanceToGo() != 0) {
    stepper.run();  // Esta função deve ser chamada até o movimento estar completo
  }
  delay(1000);
}
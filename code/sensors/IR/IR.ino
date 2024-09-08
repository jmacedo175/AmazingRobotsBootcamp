const int sensorPin = 35; //PIN analógico - ADC

#define VOLTAGE 3.3
#define MIN_ANALOG 0
#define MAX_ANALOG 4096.0

long duration;
float distanceCm;

void setup() {
  Serial.begin(9600); // Início da Comunicação em Série

  while (!Serial) ; // Espera ter um porto para connectar
  Serial.println("start");
  pinMode(sensorPin, INPUT); // Coloca o sensorPin como Input
}

void loop() {
      // Ler o valor analógico do sensor
      float analogValue = analogRead(sensorPin);

      float tensor = VOLTAGE * (analogValue/MAX_ANALOG);

      float distanceCm = 29.988 * pow(tensor, -1.173);

      //Imprimir a distância em cm
      Serial.print("Distance (cm): ");  
      Serial.print(distanceCm);
      
      delay(1000);
}

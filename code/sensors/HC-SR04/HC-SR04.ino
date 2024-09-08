const int trigPin = 5;
const int echoPin = 18;

//Definir a velocidade do som em cms por segundos
#define SOUND_SPEED 0.034

long duration;
float distanceCm;

void setup() {
  Serial.begin(9600); // Início da Comunicação em Série
  pinMode(trigPin, OUTPUT); // Colocar o trigPin como Output
  pinMode(echoPin, INPUT); // Colocar o echoPin como Input
}

void loop() {
  // Limpar o trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Colocar o trigPin em estado HIGH por 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Leitura do echoPin que devolve o tempo do percurso da onda sonora em microsegundos
  duration = pulseIn(echoPin, HIGH);
  
  // Calcula a distância
  distanceCm = duration * SOUND_SPEED/2;
  
  // Imprime a distância no Serial Monitor (Tools -> Serial Monitor)
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  delay(1000);
}

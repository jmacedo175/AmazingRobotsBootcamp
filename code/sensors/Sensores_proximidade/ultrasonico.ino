void ultrasonico_loop() {
// Limpar o trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Colocar o trigPin em estado HIGH por 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  float duration = pulseIn(echoPin, HIGH);
  
  // Calcula a distância
  float distanceCm = duration * SOUND_SPEED/2;

  Serial.print("Ultrasonico, distância (cm): ");
  Serial.println(distanceCm);
}
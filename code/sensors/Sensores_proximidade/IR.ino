void IR_loop() {

      float analogValue = analogRead(sensorPin);

      float tensor = VOLTAGE * (analogValue/MAX_ANALOG);

      float distanceCm = 29.988 * pow(tensor, -1.173);

      Serial.print("IR, distância (cm): ");
      Serial.println(distanceCm);  
}
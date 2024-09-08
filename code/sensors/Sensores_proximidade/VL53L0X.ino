void VL53_loop() {
  VL53L0X_RangingMeasurementData_t measure;
  // A função rangingTest ativa o sensor para medir a distância de um objeto à frente dele.
  // O resultado é armazenado na variável measure.
  lox.rangingTest(&measure, false);  // Ao passar false, a função executa a medição normalmente,
                                     //sem imprimir informações extras na saída serial.


  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    float distanceCm = measure.RangeMilliMeter*0.1;

    Serial.print("VL53L0X, distância (cm): ");
    Serial.println(distanceCm);
  }

  
}
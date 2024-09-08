
// Incluir a biblioteca ESP32 Arduino Servo Library:
//https://github.com/madhephaestus/ESP32Servo/tree/master
#include <ESP32Servo.h> 

Servo myservo1;  //criar um objeto do tipo servo
Servo myservo2;  //criar um objeto do tipo servo
int servoPin1 = 2;  // Pin usado 
int servoPin2 = 4;
void setup(){
  myservo1.attach(servoPin1); //associar o pin utilizado
  myservo2.attach(servoPin2); //associar o pin utilizado
 
}

void loop() {
  myservo1.write(90); // baixo
  
  
  myservo2.write(0); // cima
  delay(1000); // esperar 1 segundo

  myservo1.write(0); // cima
  myservo2.write(90); //baixo
  delay(1000); // esperar 1 segundo*/
}
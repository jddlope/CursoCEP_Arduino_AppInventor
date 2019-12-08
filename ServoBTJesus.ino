/*
 * Programa para controlar la posición de un servo desde App Inventor mediante
 * un slider y via Bluetooth usando el HC06
 * Copiado y modificado de Jose Pujol
 * Diciembre de 2019
 */


#include <Servo.h> // incluimos la libreria Servo.h
Servo servoMotor;  // Creamos el objeto tipo servo de nombre servoMotor

// Variables para recibir y almacenar datos
int byteEntrada;      // variable para leer los bytes de entrada
int valor = 0;  // variable para almacenar el valor numerico
int angulo = 0; // variable para enviar los grados al servomotor

void setup() {
  // inicializamos el led como pin digital salida
  Serial.begin(9600);;
  servoMotor.attach(11);  // conecta el servo al pin 11
}

void loop() {
  // comprobamos si hay datos de entrada
  if (Serial.available() > 0) {
    // lectura del byte mas antiguo del buffer serial
    byteEntrada = Serial.read();
    if (byteEntrada >= '0' && byteEntrada <= '9') {
      //Acumula los datos numericos multiplicando por 10 el valor acumulado
      valor = (valor * 10) + (byteEntrada - '0'); // Resta 48 que es el valor decimal del 0 ASCII
    }
    else if (byteEntrada == '>') // uso > como finalizador
    {
      angulo = valor;   // Guarda el valor en la variable angulo
      Serial.println(angulo);     // imprime angulo por monitor serie
      valor = 0;  // Dejamos lista la variable para volver a escribir en ella
    }
  }
  servoMotor.write(angulo);   // Escribimos el valor angulo en el servo
  delay(15);              // damos tiempo al servo a posicionarse
}

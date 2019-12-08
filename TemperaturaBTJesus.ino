
int incomingByte;      // variable para leer los bytes de entrada
// variables globales, aunque las 2 últimas se podrían declarar en el loop
const int LM35Pin = A0; // pin conexion
float temperatura = 0; // variable almacenar lectura
float voltaje = 0; // variable para almacenar el voltaje

void setup() {
  // inicializamos la comunicacion serie
  Serial.begin(9600);
  // aumentamos la precisión cambiando el valor de referencia para el valor 1023 en los pines analógicos
  analogReference(INTERNAL); // con el parámetro INTERNAL toma como referencia un voltaje interno de 1.1V
}

void loop() {
  // leemos el sensor
  int lectura = analogRead(LM35Pin); // Valor entre 0 y 1023
  // convertimos la lectura a voltios
  voltaje = (1.1 * lectura)/1023.0; // valor entre 0 y 1.1
  // convertimos los voltios a ºC. Según el datasheet del LM35 Voltaje (V) = 10mV/ºC * Temperatura (ºC)
  temperatura = 100.0 * voltaje;
  // comprobamos si hay datos de entrada
  if (Serial.available() > 0) {
    // lectura del byte mas antiguo del buffer serial
    incomingByte = Serial.read();
    // si el byte es T envia dato de temperatura
    if (incomingByte == 'T') {
      Serial.print(temperatura);
      Serial.print("\n"); // Esto manda un delimitador (fin de línea) para que AppInventor lo reconozca
      // Serial.println(" C") Esto es para usar sin Bluetooth, solo por el Monitor serie
    }
  }
  delay(200);
}

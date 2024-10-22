//=============[CÓDIGO PARA GENERAR SEÑAL DIGITAL CON RETARDO PARA CONTROL RECTIFICADOR SEMICONTROLADO CON SCR]======================

const int inputPin = 2;    // Pin digital al que está conectada la entrada (debe ser un pin de interrupción)
const int outputPin1 = 3;  // Primer pin de salida digital para el primer SCR
const int outputPin2 = 4;  // Segundo pin de salida digital para el segundo SCR
volatile float valpot = 3;
const int t_min = 2, t_max = 9000;

void setup() {
  Serial.begin(115200);  // Inicializa la comunicación serial a 115200 bps
  pinMode(inputPin, INPUT);
  pinMode(outputPin1, OUTPUT);  // Configura el primer pin de salida como salida
  pinMode(outputPin2, OUTPUT);  // Configura el segundo pin de salida como salida

  // Configura las salidas inicialmente en estado lógico alto (1)
  digitalWrite(outputPin1, HIGH);
  digitalWrite(outputPin2, HIGH);
  delay(1000);

  // attachInterrupt(digitalPinToInterrupt(inputPin), readInput, RISING); // Configura la interrupción en el pin de entrada
}

void loop() {
  valpot = (map(analogRead(A0), 0, 1024, t_min, t_max));  //Limita el rango de valores.
  Serial.println(valpot);                                   //Expresado en microsegundos.
  //Serial.println(" micro segundos");
  if (digitalRead(inputPin) == true) {
    //---------- Si cumple con el rango  (0,3ms] -----------
    if (valpot > 0 && valpot <= 3)  // Evita errores en extremos. 3 us es el mínimo valor para función delayMicroseconds.
    {
      digitalWrite(outputPin1, HIGH);
      digitalWrite(outputPin2, HIGH);
    }
    //---------- Si cumple con el rango  (3,~8ms) -----------
    else if (valpot > 3 && valpot < 7532)  // Evita errores en extremos. 3 us es el mínimo valor para función delayMicroseconds.
    {
      digitalWrite(outputPin1, LOW);
      digitalWrite(outputPin2, LOW);
      delayMicroseconds(valpot);
      digitalWrite(outputPin1, HIGH);
      digitalWrite(outputPin2, HIGH);
    }
    //---------- Si cumple con el rango  [8,inf ms) -----------
    else if (valpot >= 7532)  // Evita errores en extremos. 3 us es el mínimo valor para función delayMicroseconds.
    {
      digitalWrite(outputPin1, LOW);
      digitalWrite(outputPin2, LOW);
    }
  }
}

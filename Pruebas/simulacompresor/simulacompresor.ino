
const int consumoInPin = A0;  // Analog input pin that the potentiometer is attached to
const int tempOutPin = 10; // Analog output pin that the LED is attached to
const int generacionInPin = A1;  // Analog input pin that the potentiometer is attached to
const int presionOutPin = 11; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
float temperatura = 0;        // value output to the PWM (analog out)
float presion = 100;        // value output to the PWM (analog out)
float deltaPresion = 0;
int deltaTemp = 0;
int outPresion = 0;
int outTemp = 0;
int maxTemp = 25000;
int minTemp = 100;
int maxPresion =25000;
int consumo = 0;
int generacion = 0;

void setup() {
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  delay(2);
  consumo = analogRead(consumoInPin);
  delay(2);
  generacion = analogRead(generacionInPin);
  
  deltaPresion = -(consumo / 100);
  if (digitalRead(3)==HIGH)  {
    presion = presion -5;
    maxTemp = 100;
    minTemp = 100;
    deltaTemp = 20;
  }
  if (digitalRead(3)==LOW)  {
    if (digitalRead(4)==LOW) {
      deltaPresion = ((generacion / 100) - (consumo / 100)); 
      maxTemp = 25000;
      minTemp = 24000;
      deltaTemp = 10;
    }
    else
    {
      deltaPresion = -((generacion / 100) - (consumo / 100)); 
      maxTemp = 22000;
      minTemp = 20000;
      deltaTemp = 5;
    }
  }

  presion = presion + deltaPresion;

  if (presion < 10) {
    presion = 10;
  }
  if (presion > maxPresion) {
    presion = maxPresion;
  }
  if (temperatura < minTemp) {
    temperatura = temperatura + deltaTemp;
  }
  if (temperatura > maxTemp) {
    temperatura = temperatura - deltaTemp;
  }
  
  outTemp = temperatura / 100;
  outPresion = presion /100;
  
  analogWrite(tempOutPin, outTemp);
  analogWrite(presionOutPin, outPresion);
  
  // print the results to the serial monitor:
  Serial.print("\n generado = " );
  Serial.print(generacion);
  Serial.print("\t consumo = " );
  Serial.print(consumo);

  Serial.print("\t temp = " );
  Serial.print(outTemp);

  Serial.print("\t delta = " );
  Serial.print(deltaPresion);
  
  Serial.print("\t presion = ");
  Serial.print(outPresion);

  delay(10);
}

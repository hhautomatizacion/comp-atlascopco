/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int consumoInPin = A0;  // Analog input pin that the potentiometer is attached to
const int tempOutPin = 10; // Analog output pin that the LED is attached to
const int generacionInPin = A1;  // Analog input pin that the potentiometer is attached to
const int presionOutPin = 11; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
float temperatura = 0;        // value output to the PWM (analog out)
float presion = 100;        // value output to the PWM (analog out)
float delta = 0;
int outPresion = 0;
int outTemp = 0;
int maxTemp = 25000;
int maxPresion =25000;
int consumo = 0;
int generacion = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  consumo = analogRead(consumoInPin);
  delay(3);
  //generacion = analogRead(generacionInPin);
  generacion = 600;
  delta = -(consumo / 100);
  if (digitalRead(3)==LOW)  {
    if (temperatura < maxTemp) {
      temperatura = temperatura +2;
    }
  }
  if (digitalRead(3)==HIGH)  {
    presion = presion -1;
    if (temperatura > 100 ) {
      temperatura = temperatura -1;
    }
  }
  if (digitalRead(3)==LOW)  {
    if (digitalRead(4)==LOW) {
      delta = ((generacion / 100) - (consumo / 100)); 
      if (temperatura < maxTemp) {
        temperatura = temperatura +2;
      }
    }
    else
    {
      delta = -((generacion / 100) - (consumo / 100)); 
    }
  }

  presion = presion + delta;

  if (presion < 10) {
   presion = 10;
  }
  if (presion > maxPresion) {
    presion = maxPresion;
  }
  
  outTemp = temperatura / 100;
  outPresion = presion /100;
  
  analogWrite(tempOutPin, outTemp);
  analogWrite(presionOutPin, outPresion);
  
  // print the results to the serial monitor:
    Serial.print("\t generado = " );
  Serial.print(generacion);
  Serial.print("\t consumo = " );
  Serial.print(consumo);

  
  Serial.print("\t temp = " );
  Serial.print(outTemp);

  Serial.print("\t delta = " );
  Serial.print(delta);
  

  Serial.print("\t presion = ");
  Serial.println(outPresion);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(10);
}

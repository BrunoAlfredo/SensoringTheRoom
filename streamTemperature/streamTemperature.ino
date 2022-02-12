
/* Credits to Bruno Alves, created 09/11/2021*/

/* LN35 SENSOR:
   Arduino Uno contains a multichannel, 10-bit analog to digital converter. 
   This means that it will map input voltages between 0 and the operating 
   voltage 5V into integer values between 0 and 1023. However, the sensor
   only produces voltages from 0 to +1V. The ADC uses 5V as the highest
   possible value. This is wasting 80% of the possible range. 
   If you change aRef to 1.1V, you will get almost the highest resolution
   possible.

   Using 1.1V as aRef, the equation changes. If you divide 1.1V over 1024, 
   each step up in the analog reading is equal to approximately 1.0742 mV. 
   If 10mV is equal to 1 degree Celcius, 10 / 1.0742 = ~9.31. So, for every 
   change of 9.31 in the analog reading, there is one degree of temperature 
   change.
 */

/* DHT11 SENSOR:
   Temperature and humidity sensor. Relevant specifications:
    - humidity accuracy is +-5%
    - temperature accuracy is +-2ºC
    - resolution is 1 for both entities
 */

#include "DHT.h"

// LN35 Sensor
constexpr float BASE_CELSIUS = 9.31;
constexpr short int measureEvery = 5*60*1000;
constexpr byte numberOfSamplesAverage = 3;
byte analogPin = 1;

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Data
byte temp35 = 0;
byte temp11 = 0;
byte humid = 0;

void setup() {
  Serial.begin(9600);

  // Setup for LN35 sensor
  analogReference(INTERNAL); // change aRef to 1.1V

  dht.begin();
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {  
  measureFromLn35InCelsius(&temp35);
  measureFromDht11(&temp11, &humid);
  activateLedNotification();
  displayDataOnSerial();
}

void  measureFromLn35InCelsius(byte* result) {
  (*result) = 0;
  for (byte i=0; i<numberOfSamplesAverage; i++) {
    (*result) += analogRead(analogPin)/BASE_CELSIUS;
  }
  (*result) = (byte) (*result)/numberOfSamplesAverage;
}

void measureFromDht11(byte* temp, byte* hum) {
  (*temp) = (byte) dht.readTemperature();
  (*hum) = (byte) dht.readHumidity();
}

void activateLedNotification() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
}

void displayDataOnSerial() {
  Serial.print(temp35);
  if (!(isnan(temp11) || isnan(humid))) {
    Serial.print(", ");
    Serial.print(temp11);
    Serial.print(", ");
    Serial.print(humid);
  }
  Serial.println();
}

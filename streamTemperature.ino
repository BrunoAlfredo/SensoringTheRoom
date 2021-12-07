
/* Credits to Bruno Alves, created 09/11/2021
 * Goal: collect temperature from a LN35 sensor
 *       stream that data to the computer 
 *       produce visualization of the data
 */

/* MEASUREMENT:
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

constexpr float BASE_CELSIUS = 9.31;
constexpr short int measureEvery = 5*60*1000;
constexpr byte numberOfSamplesAverage = 3;

byte analogPin = 1;

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL); // change aRef to 1.1V
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  float temperature = readCelsiusTemperatureanalogRead();
  activateLedNotification();
  Serial.print(temperature);
  Serial.println();
  delay(measureEvery);
  // this delay does not work properly
}

float readCelsiusTemperatureanalogRead() {
  float sum=0.0;
  for (byte i=0; i<numberOfSamplesAverage; i++) {
    sum += analogRead(analogPin)/BASE_CELSIUS;
  }
  return sum/numberOfSamplesAverage;
}

void activateLedNotification() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
}
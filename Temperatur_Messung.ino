#include <math.h>

const double vcc = 3.3; //Volts
const int tempRaw = 26; //ADC PIN
const int res0 = 10000; //Ohm#
const double a = 1.122775062e-3; // 1000;
const double b = 2.358874358-4; // 10000;
const double c = 0.7504998806e-7; // 10000000;
const double resolution = 4095;

void setup() {
  Serial.begin(115200);
  //pinMode(tempVoltage, INPUT);
}

double calcTemp(int rawADC){
  //local variables
  double temp;
  double resistor;
  double voltage;

  voltage = (rawADC/resolution) * vcc;
  Serial.printf("%lfV \n", voltage);
  resistor = (10000 * voltage) / (vcc - voltage);
  Serial.printf("%lfOhm \n" ,resistor);

  temp = 1 / (a + b * log(resistor) + c * pow(log(resistor), 3));
  Serial.printf("%lfK \n", temp);
  return temp - 273.1;
}

void loop() {
  int adcRead = analogRead(tempRaw);

  double temperature = calcTemp(adcRead);

  Serial.printf("%lf°C \n" ,temperature);
  delay(1000);
}

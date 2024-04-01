#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BMP_SCL 13
#define BMP_SDO 12
#define BMP_SDA 11

#define BMP_CSB1 10
#define BMP_CSB2 9

Adafruit_BMP280 bmp1(BMP_CSB1, BMP_SDA, BMP_SDO, BMP_SCL);

Adafruit_BMP280 bmp2(BMP_CSB2, BMP_SDA, BMP_SDO, BMP_SCL);


void setup() {
  Serial.begin(9600);

  // Set chip select pins as outputs
  pinMode(BMP_CSB1, OUTPUT);
  pinMode(BMP_CSB2, OUTPUT);

  // Set chip select pins high to deselect both sensors initially
  digitalWrite(BMP_CSB1, HIGH);
  digitalWrite(BMP_CSB2, HIGH);

  Serial.println("Starting BMP280 device 1...");
  Serial.println(bmp1.begin());

  if (!bmp1.begin()) {
    Serial.println("Sensor BMP280 device 1 was not found.");
  //   while (1);
  }
  // Serial.println("Initialize BMP280 1 completed.");
  delay(2000);

  Serial.println("Starting BMP280 device 2...");

  if (!bmp2.begin()) {
    Serial.println("Sensor BMP280 device 2 was not found.");
  //    while (1);
  }
  // Serial.println("Initialize BMP280 2 completed.");
  delay(2000);


}  

void loop() {
  float pressure = bmp1.readPressure();
  Serial.print("Pressure 1 = ");
  Serial.print(pressure);
  Serial.print("Pa,   ");
  Serial.print("\t");
  delay(100);

  float pressure2 = bmp2.readPressure();
  Serial.print("Pressure 2 = ");
  Serial.print(pressure2);
  Serial.print("Pa,   ");
  Serial.println();
  delay(100);

}
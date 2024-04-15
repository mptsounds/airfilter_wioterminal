// SPI + I2C test code:


#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>


#define BMP_SCL PIN_SPI_SCK // 3rd pin of BMP280, SCK. Pin 23 (PIN_SPI_SCK)
#define BMP_SDO PIN_SPI_MISO // 6th pin, MISO (Master IN Slave OUT). Pin 21 (PIN_SPI_MISO)
#define BMP_SDA PIN_SPI_MOSI // 4th pin, MOSI (Master OUT Slave IN). Pin 19 (PIN_SPI_MOSI)

#define BMP_CSB2 PIN_SPI_SS // 5th pin bmp1 (Slave SELECT). Pin 24 (PIN_SPI_SS)
// #define BMP_CSB2 32 // 5th pin bmp2 (Slave SELECT). Tried: pin 7, 13, 16, 26, 32, 33

// Currently: 3.3V to Pin 1, GND to 6, SCK to 23, MOSI to 19, CS1 to 24, MISO to 21, CS2 see above.

#define BMP280_ADDRESS_1 0x76
  // BMP280_REGISTER_CONTROL = 0xF4,
  // BMP280_REGISTER_PRESSUREDATA = 0xF7,

Adafruit_BMP280 bmp1; // I2C

Adafruit_BMP280 bmp2(BMP_CSB2, BMP_SDA, BMP_SDO, BMP_SCL); // SPI




void setup() {

  Serial.begin(9600);

  delay(5000);

  // Serial.print("\t");
  Serial.println("Starting BMP280 device 2...");
  Serial.println("Sensor 2 status: " + String(bmp2.begin()));

  if (!bmp2.begin()) {
    Serial.println("Sensor BMP280 device 2 was not found.");
  //   while (1);
  }
  // Serial.println("Initialize BMP280 2 completed.");

  delay(2000);

  Serial.println("Starting BMP280 device 1...");
  Serial.println("Sensor 1 status: " + String(bmp1.begin()));

  unsigned BMP280_status_1;
  BMP280_status_1 = bmp1.begin(BMP280_ADDRESS_1);
  Serial.println("BMP280 1 status: " + String(BMP280_status_1));

  if (!BMP280_status_1) { // if BMP280_status_1 <> 1
    Serial.println(F("Could not find a valid BMP280 sensor. Check wiring (after TURNING OFF the device) or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp1.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    // while (1) delay(10); // can't exit this loop unless BMP_status is empty
  }
     else {
     Serial.print("Detected BMP280 1. Proceeding...");
   }
  /* Default settings from the datasheet. */
  bmp1.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

}  

void loop() {
  digitalWrite(BMP_CSB2, LOW);

  float pressure = bmp2.readPressure();
  Serial.print("Pressure 2 = ");
  Serial.print(pressure);
  Serial.print(" Pa,   ");
  Serial.print("\t");
  delay(100);

  digitalWrite(BMP_CSB2, HIGH);


  float pressure1 = bmp1.readPressure();
  Serial.print("Pressure 1 = ");
  Serial.print(pressure1);
  Serial.print(" Pa,   ");
  Serial.println();
  delay(100);



}
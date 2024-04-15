// #define BLYNK_TEMPLATE_ID           "TMPL6NfKCUElu"
// #define BLYNK_TEMPLATE_NAME         "Quickstart Template"
// #define BLYNK_AUTH_TOKEN            "559-aXOVdHaiRiybcUt_J8HGcaFYR0tS"
// #define BLYNK_PRINT Serial
// #include <Arduino.h>
// // #include "TFT_eSPI.h" //** disable this??
// // #include "Free_Fonts.h" // used a diff way to set font type & size
// TFT_eSPI tft;
// TFT_eSprite spr = TFT_eSprite(&tft);
// #include <rpcWiFi.h>
// #include <WiFiClient.h>
// #include <BlynkSimpleWioTerminal.h>
// #include <SensirionI2CSen5x.h>
// #include <Adafruit_BMP280.h>
// #include <Adafruit_Sensor.h> // from BMP280 code
// #include <Wire.h>
// #include <SPI.h> // from BMP280 code

// #define BMP_SCL (23) // 3rd pin of BMP280, SCK. Pin 23 (PIN_SPI_SCLK)
// #define BMP_SDO (21) // 6th pin, MISO (Master IN Slave OUT). Pin 21 (PIN_SPI_MISO)
// #define BMP_SDA (19) // 4th pin, MOSI (Master OUT Slave IN). Pin 19 (PIN_SPI_MOSI)

// #define BMP_CSB1 (24) // 5th pin bmp1 (Slave SELECT). Pin 24 (PIN_SPI_SS)
// #define BMP_CSB2 (32) // 5th pin bmp2 (Slave SELECT). Tried: pin 7, 13, 16, 26, 32

// // Currently: 3.3V to Pin 1, GND to 6, SCL to 23, MOSI to 19, CS1 to 24, MISO to 21, CS2 see above.

// Adafruit_BMP280 bmp1(BMP_CSB1, BMP_SDA, BMP_SDO, BMP_SCL);

// Adafruit_BMP280 bmp2(BMP_CSB2, BMP_SDA, BMP_SDO, BMP_SCL);

// //###############################################

// // Wi-Fi credentials:
// char ssid[] = "Toong-Guest";
// char pass[] = "toong@2017";

// BlynkTimer timer;

// // This function is called every time the device is connected to the Blynk.Cloud
// BLYNK_CONNECTED()
// {
//   // Change Web Link Button message to "Congratulations!"
//   Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
//   Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
//   Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
// }


// void setup() {
//   Serial.begin(9600); //not 115200

//   Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

//   // Set chip select pins as outputs
//   pinMode(BMP_CSB1, OUTPUT);
//   pinMode(BMP_CSB2, OUTPUT);
  
//   Serial.println("Starting BMP280 device 1...");
//   Serial.println(bmp1.begin());

//   if (!bmp1.begin()) {
//     Serial.println("Sensor BMP280 device 1 was not found.");
//     // while (1);
//   }
//   // Serial.println("Initialize BMP280 1 completed.");
//   delay(2000);

//   Serial.println("Starting BMP280 device 2...");
//   Serial.println(bmp2.begin());


//   if (!bmp2.begin()) {
//     Serial.println("Sensor BMP280 device 2 was not found.");
//     //  while (1);
//   }
//   // Serial.println("Initialize BMP280 2 completed.");
//   delay(2000);

//   // // Set chip select pins high to deselect both sensors initially
//   // digitalWrite(BMP_CSB1, HIGH);
//   // digitalWrite(BMP_CSB2, HIGH);

// }  

// void loop() {

//   Blynk.run();
//   timer.run();

//   // digitalWrite(BMP_CSB1, LOW);  // Select sensor 1

//   float pressure = bmp1.readPressure();
//   Serial.print("Pressure 1 = ");
//   Serial.print(pressure);
//   Serial.print("Pa,   ");
//   Serial.print("\t");
//   delay(100);

//   // digitalWrite(BMP_CSB2, LOW);  // Select sensor 2

//   float pressure2 = bmp2.readPressure();
//   Serial.print("Pressure 2 = ");
//   Serial.print(pressure2);
//   Serial.print("Pa,   ");
//   Serial.println();
//   delay(100);

// }


// ARDUINO UNO TEST CODE:
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
// #include <Wire.h>

#define BMP_SCL PIN_SPI_SCK // 3rd pin of BMP280, SCK. Pin 23 (PIN_SPI_SCK)
#define BMP_SDO PIN_SPI_MISO // 6th pin, MISO (Master IN Slave OUT). Pin 21 (PIN_SPI_MISO)
#define BMP_SDA PIN_SPI_MOSI // 4th pin, MOSI (Master OUT Slave IN). Pin 19 (PIN_SPI_MOSI)

#define BMP_CSB1 PIN_SPI_SS // 5th pin bmp1 (Slave SELECT). Pin 24 (PIN_SPI_SS)
#define BMP_CSB2 32 // 5th pin bmp2 (Slave SELECT). Tried: pin 7, 13, 16, 26, 32, 33

// Currently: 3.3V to Pin 1, GND to 6, SCK to 23, MOSI to 19, CS1 to 24, MISO to 21, CS2 see above.

#define BMP280_ADDRESS_1 0x77
  // BMP280_REGISTER_CONTROL = 0xF4,
  // BMP280_REGISTER_PRESSUREDATA = 0xF7,


Adafruit_BMP280 bmp1(BMP_CSB1, BMP_SDA, BMP_SDO, BMP_SCL);

Adafruit_BMP280 bmp2(BMP_CSB2, BMP_SDA, BMP_SDO, BMP_SCL);



void setup() {

  Serial.begin(9600);

  // SPI.begin();
  // bmp1.begin();

  // // Set chip select pins high to deselect both sensors initially
  // digitalWrite(BMP_CSB1, HIGH);
  // digitalWrite(BMP_CSB2, HIGH);

  delay(5000);

  // Serial.print("\t");
  Serial.println("Starting BMP280 device 1...");
  Serial.println("Sensor 1 status: " + String(bmp1.begin()));

  if (!bmp1.begin()) {
    Serial.println("Sensor BMP280 device 1 was not found.");
  //   while (1);
  }
  // Serial.println("Initialize BMP280 1 completed.");

  delay(2000);

  Serial.println("Starting BMP280 device 2...");
  Serial.println("Sensor 2 status: " + String(bmp2.begin()));


  if (!bmp2.begin()) {
    Serial.println("Sensor BMP280 device 2 was not found.");
  //    while (1);
  }
  // Serial.println("Initialize BMP280 2 completed.");
  delay(2000);

  // // Set chip select pins high to deselect both sensors initially
  // digitalWrite(BMP_CSB1, HIGH);
  // digitalWrite(BMP_CSB2, HIGH);

}  

void loop() {
  digitalWrite(BMP_CSB1, LOW);

  float pressure = bmp1.readPressure();
  Serial.print("Pressure 1 = ");
  Serial.print(pressure);
  Serial.print(" Pa,   ");
  Serial.print("\t");
  delay(100);

  digitalWrite(BMP_CSB1, HIGH);

  digitalWrite(BMP_CSB2, LOW);

  float pressure2 = bmp2.readPressure();
  Serial.print("Pressure 2 = ");
  Serial.print(pressure2);
  Serial.print(" Pa,   ");
  Serial.println();
  delay(100);

  digitalWrite(BMP_CSB2, LOW);


}
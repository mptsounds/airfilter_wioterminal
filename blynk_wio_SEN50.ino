#define BLYNK_TEMPLATE_ID           "TMPL6NfKCUElu"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "559-aXOVdHaiRiybcUt_J8HGcaFYR0tS"
#define BLYNK_PRINT Serial
#include <Arduino.h>
#include "TFT_eSPI.h"
#include "Free_Fonts.h"
TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);
#include <rpcWiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleWioTerminal.h>
#include <SensirionI2CSen5x.h>
// #include <Adafruit_BMP280.h>

#include <Wire.h>
// #include <SPI.h> // from BMP280 code

#define MAXBUF_REQUIREMENT 48
#if (defined(I2C_BUFFER_LENGTH) &&                 \
     (I2C_BUFFER_LENGTH >= MAXBUF_REQUIREMENT)) || \
    (defined(BUFFER_LENGTH) && BUFFER_LENGTH >= MAXBUF_REQUIREMENT)
#define USE_PRODUCT_INFO
#endif
SensirionI2CSen5x sen5x;

#define BMP280_ADDRESS 0x76
Adafruit_BMP280 bmp; // I2C
//###############################################

char ssid[] = "Toong-Guest";
char pass[] = "toong@2017";

BlynkTimer timer;

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
//void myTimerEvent()
//{
//  // You can send any value at any time.
//  // Please don't send more that 10 values per second.
//  Blynk.virtualWrite(V2, millis() / 1000);
//}

void setup()
{
  // Debug console
  Serial.begin(115200);
  //--------------------------Blynk---------------------
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // Setup a function to be called every second
  //timer.setInterval(1000L, myTimerEvent);
  //--------------------------LCD---------------------
      tft.begin();
      tft.setRotation(3);
      tft.fillScreen(TFT_BLACK);

      tft.fillRect(0, 0,320,50, TFT_YELLOW);
      tft.setFreeFont(FSB18);
      tft.setTextColor(TFT_BLACK);
      tft.drawString("FAN CLEANNING", 10, 15); // drawString syntax: (text, xpos, ypos, [font size])

      tft.setTextColor(TFT_WHITE);
      tft.setFreeFont(FS18);
      tft.drawString("OPERATING", 60, 100);
      tft.drawString("Please wait 10 sec", 30, 160);
      
  //--------------------------SEN50---------------------
    Wire.begin();
    sen5x.begin(Wire);

    uint16_t error;
    char errorMessage[256];
    error = sen5x.deviceReset();
    if (error) {
        Serial.print("Error trying to execute deviceReset(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }
    // Start Measurement
    error = sen5x.startMeasurement();
    if (error) {
        Serial.print("Error trying to execute startMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }
      Serial.print("\t");
  Serial.print("Fan Cleaning");
  Serial.println("");
  sen5x.startFanCleaning();
  delay(10000);
      tft.fillScreen(TFT_BLACK);
      tft.fillRect(0, 0,320,50, TFT_YELLOW);
      tft.setFreeFont(FSB18);
      tft.setTextColor(TFT_BLACK);
      tft.drawString("AIR QUALITY", 40, 15);

      tft.setTextColor(TFT_WHITE);
      tft.setFreeFont(FS18);
      tft.drawString("PM1.0", 10, 60);
      tft.drawString("PM2.5", 10, 110);
      tft.drawString("PM4.0", 10, 160);
      tft.drawString("PM10.0", 10, 210);

  //--------------------------BMP280---------------------
 Serial.println(("BMP280 test"));
  unsigned BMP280_status;
  BMP280_status = bmp.begin(BMP280_ADDRESS);
  Serial.println("?");
  // Serial.println(status);
  if (!BMP280_status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
     else {
     Serial.print("Detected BMP280. Proceeding...");
   }
  /* Default settings from the datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  delay(1000);
      tft.fillScreen(TFT_BLACK);
      tft.fillRect(0, 0,320,80, TFT_YELLOW);
      tft.setFreeFont(FSB18);
      tft.setTextColor(TFT_BLACK);
      tft.drawString("Check BMP280 (pressure sensor) status in serial monitor", 40, 15); // tft.drawString([a string], [x-coor], [y-coor])

}

void loop()
{
  Blynk.run();
  timer.run();

  uint16_t error;
  char errorMessage[256];

    delay(1000);

    // Read Measurement
    float massConcentrationPm1p0;
    float massConcentrationPm2p5;
    float massConcentrationPm4p0;
    float massConcentrationPm10p0;

    error = sen5x.readMeasuredValuesSen50(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0);

    if (error) {
        Serial.print("Error trying to execute readMeasuredValues(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        Serial.print("MassConcentrationPm1p0:");
        Serial.print(massConcentrationPm1p0);
        Serial.print("\t");
        Serial.print("MassConcentrationPm2p5:");
        Serial.print(massConcentrationPm2p5);
        Serial.print("\t");
        Serial.print("MassConcentrationPm4p0:");
        Serial.print(massConcentrationPm4p0);
        Serial.print("\t");
        Serial.print("MassConcentrationPm10p0:");
        Serial.print(massConcentrationPm10p0);
        Serial.print("\n");
     //Sprite buffer for pm1p0
        spr.createSprite(120, 40); //create buffer
        spr.fillSprite(TFT_BLACK); //fill background color of buffer
        spr.setFreeFont(FMB18); //set font type 
        if(massConcentrationPm1p0<=15)
          spr.setTextColor(TFT_GREEN);
        else
          spr.setTextColor(TFT_RED);
        spr.drawFloat(massConcentrationPm1p0, 2, 0, 0); //display number 
        spr.pushSprite(150, 60); //push to LCD 
        spr.deleteSprite(); //clear buffer

     //sprite buffer for pm2p5
        spr.createSprite(120, 40);
        spr.fillSprite(TFT_BLACK);
        spr.setFreeFont(FMB18);
        if(massConcentrationPm1p0<=15)
          spr.setTextColor(TFT_GREEN);
        else
          spr.setTextColor(TFT_RED);
        spr.drawFloat(massConcentrationPm2p5, 2, 0, 0); 
        spr.pushSprite(150, 110);
        spr.deleteSprite();
        
      //sprite buffer for pm4p0
        spr.createSprite(120, 40);
        spr.fillSprite(TFT_BLACK);
        spr.setFreeFont(FMB18);
        if(massConcentrationPm1p0<=15)
          spr.setTextColor(TFT_GREEN);
        else
          spr.setTextColor(TFT_RED);
        spr.drawFloat(massConcentrationPm4p0, 2, 0, 0); 
        spr.pushSprite(150, 160);
        spr.deleteSprite();

      //sprite buffer for pm10p0
        spr.createSprite(120, 40);
        spr.fillSprite(TFT_BLACK);
        spr.setFreeFont(FMB18);
        if(massConcentrationPm1p0<=15)
          spr.setTextColor(TFT_GREEN);
        else
          spr.setTextColor(TFT_RED);
        spr.drawFloat(massConcentrationPm10p0, 2, 0, 0); 
        spr.pushSprite(150, 210);
        spr.deleteSprite();
}
    Blynk.virtualWrite(V0, massConcentrationPm1p0);
    Blynk.virtualWrite(V1, massConcentrationPm2p5);
    Blynk.virtualWrite(V2, massConcentrationPm4p0);
    Blynk.virtualWrite(V3, massConcentrationPm10p0);
}

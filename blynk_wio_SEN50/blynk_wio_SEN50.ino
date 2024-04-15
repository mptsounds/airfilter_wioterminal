#define BLYNK_TEMPLATE_ID           "TMPL6NfKCUElu"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "559-aXOVdHaiRiybcUt_J8HGcaFYR0tS"
#define BLYNK_PRINT Serial
#include <Arduino.h> // UI-related: Compilation warmings, v2.3.2 
#include "TFT_eSPI.h" // to-do: copy this to UNO code - test
// #include "Free_Fonts.h" // used a diff way to set font type & size
TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);
#include <rpcWiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleWioTerminal.h>
#include <SensirionI2CSen5x.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h> // from BMP280 code
#include <Wire.h>
#include <SPI.h> // from BMP280 code

#define MAXBUF_REQUIREMENT 48
#if (defined(I2C_BUFFER_LENGTH) &&                 \
     (I2C_BUFFER_LENGTH >= MAXBUF_REQUIREMENT)) || \
    (defined(BUFFER_LENGTH) && BUFFER_LENGTH >= MAXBUF_REQUIREMENT)
#define USE_PRODUCT_INFO
#endif
SensirionI2CSen5x sen5x;

// BMP280 Sensor 1 - I2C communication:
#define BMP280_ADDRESS_1 0x76

// BMP280 Sensor 2 - SPI communication:
#define BMP_SCL PIN_SPI_SCK // 3rd pin of BMP280, SCK. Pin 23 on Wio Terminal
#define BMP_SDO PIN_SPI_MISO // 6th pin, MISO (Master IN Slave OUT). Pin 21
#define BMP_SDA PIN_SPI_MOSI // 4th pin, MOSI (Master OUT Slave IN). Pin 19
#define BMP_CSB2 PIN_SPI_SS // 5th pin bmp1 (Slave SELECT). Pin 24

// Objects for BMP sensors:
Adafruit_BMP280 bmp1; // I2C
Adafruit_BMP280 bmp2(BMP_CSB2, BMP_SDA, BMP_SDO, BMP_SCL); // SPI


//###############################################

// Wi-Fi credentials:
char ssid[] = "Toong-Guest";
char pass[] = "toong@2017";

// char ssid[] = "Sai Gon Sky Home 102";
// char pass[] = "@1234102";

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



//###############################################
void setup()
{
  // Debug console
  Serial.begin(115200);

  //--------------------------Blynk---------------------
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // Setup a function to be called every second
  // timer.setInterval(1000, myTimerEvent);

  //--------------------------LCD---------------------
      tft.begin();
      tft.setRotation(3);
      tft.fillScreen(TFT_BLACK);

      tft.fillRect(0, 0, 320, 50, TFT_YELLOW);
      tft.setFreeFont(&FreeSerifBold18pt7b); // select Free, Serif, Bold, 18pt
      tft.setTextColor(TFT_BLACK);
      tft.drawString("FAN CLEANNING", 10, 15); // drawString syntax: (text, xpos, ypos, [font size])

      tft.setTextColor(TFT_WHITE);
      tft.setFreeFont(&FreeSerif18pt7b);
      tft.drawString("OPERATING", 60, 100);
      tft.drawString("Please wait 10 sec", 30, 160);

  //--------------------------SEN50---------------------
    Wire.begin();
    sen5x.begin(Wire);

    // SEN50 Error handling:
    uint16_t error; // declares a var named "error" as an unsigned 16-bit integer.
    char errorMessage[256]; // declares an array named errorMessage capable of holding 256 characters
    error = sen5x.deviceReset();
    if (error) { // if this error is non-zero
        Serial.print("Error trying to execute deviceReset(): "); // at which step the error happens
        errorToString(error, errorMessage, 256); // converts the numerical error code into a human-readable error message and stores it in the errorMessage buffer
        Serial.println(errorMessage); // specific error code
    }
    // Start Measurement:
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


  //--------------------------BMP280---------------------
  // Sensor 1 setup: 

  unsigned BMP280_status_1;

  BMP280_status_1 = bmp1.begin(BMP280_ADDRESS_1);
  // Serial.println("?");
  Serial.println("BMP280 1 status: " + String(BMP280_status_1)); // status = "1" means detected

  if (!BMP280_status_1) { // if BMP280_status_1 <> 1
    Serial.println(F("Could not find the valid BMP280 1 sensor. Check wiring (after TURNING OFF the device) or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp1.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    // while (1) delay(10); // can't exit this loop unless BMP_status is empty
  }
     else {
     Serial.print("Detected BMP280. Proceeding...");
     Serial.println();

   }
  /* Default settings from the datasheet. */
  bmp1.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  bmp2.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  // Serial.println("Starting BMP280 device 2...");
  Serial.println("BMP280 2 status: " + String(bmp2.begin())); // status = "1" means detected

  if (!bmp2.begin()) {
    Serial.println(F("Could not find the valid BMP280 2 sensor. Check wiring (after TURNING OFF the device)"));
  //   while (1);
  }
  // Serial.println("Initialize BMP280 2 completed.");



  //-------------------MAIN GRAPHICS---------------------
  // delay(10000);
  //     tft.fillScreen(TFT_BLACK);
  //     tft.fillRect(0, 0,320,50, TFT_YELLOW);
  //     tft.setFreeFont(&FreeSerifBold18pt7b);
  //     tft.setTextColor(TFT_BLACK);
  //     tft.drawString("AIR QUALITY", 40, 15);

  //     tft.setTextColor(TFT_WHITE);
  //     tft.setFreeFont(&FreeSerif18pt7b);
  //     tft.drawString("PM1.0", 10, 60);
  //     tft.drawString("PM2.5", 10, 110);
  //     tft.drawString("PM4.0", 10, 160);
  //     tft.drawString("PM10.0", 10, 210);

  delay(10000); // draw the graphics
      // Left block header (Air quality):
      tft.fillScreen(TFT_BLACK);
      tft.fillRect(0, 0, 170, 40, TFT_YELLOW);
      tft.setFreeFont(&FreeSerifBold12pt7b);
      tft.setTextColor(TFT_BLACK);
      tft.drawString("AIR QUALITY", 3, 10);
      // Left block static text (PM1.0, PM2.5,..):
      tft.setTextColor(TFT_WHITE);
      tft.setFreeFont(&FreeSerif12pt7b);
      tft.drawString("PM1.0", 3, 60);
      tft.drawString("PM2.5", 3, 110);
      tft.drawString("PM4.0", 3, 160);
      tft.drawString("PM10.0", 3, 210);
      // Right block header (PRESSURE):
      tft.fillRect(175, 0, 160, 40, TFT_YELLOW);
      tft.setFreeFont(&FreeSerifBold12pt7b);
      tft.setTextColor(TFT_BLACK);
      tft.drawString("PRESSURE", 183, 10);
      // Right block static text (Init pressure, Final, Diff (in Pa)):
      tft.setTextColor(TFT_WHITE);
      tft.setFreeFont(&FreeSerif12pt7b);
      tft.drawString("Sensor 1 (Pa):", 190, 60);
      tft.drawString("Sensor 2 (Pa):", 190, 120);
      tft.drawString("Difference:", 190, 185);
      // TEST: Right block dynamic text - mock values:
      // tft.setTextColor(TFT_GREEN);
      // tft.setFreeFont(&FreeSerif12pt7b);
      // tft.drawString("100867.25", 190, 85);
      // tft.drawString("100867.63", 190, 145);
      // tft.drawString("000.00", 190, 210);


}



//###############################################
void loop()
{
  Blynk.run();
  timer.run();

// Read SEN50 values:
  uint16_t error;
  char errorMessage[256];

    delay(1000);

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
        // spr.createSprite(120, 40); //create buffer
        spr.createSprite(70, 40); //create buffer
        spr.fillSprite(TFT_BLACK); //fill background color of buffer
        spr.setFreeFont(&FreeMonoBold12pt7b);
        if(massConcentrationPm1p0<=15)
          spr.setTextColor(TFT_GREEN);
        else
          spr.setTextColor(TFT_RED);
        spr.drawFloat(massConcentrationPm1p0, 2, 0, 0); //display number 
        spr.pushSprite(90, 60); //push to LCD 
        spr.deleteSprite(); //clear buffer

     //sprite buffer for pm2p5
        spr.createSprite(70, 40);
        spr.fillSprite(TFT_BLACK);
        spr.setFreeFont(&FreeMonoBold12pt7b);
        if(massConcentrationPm1p0<=15)
          spr.setTextColor(TFT_GREEN);
        else
          spr.setTextColor(TFT_RED);
        spr.drawFloat(massConcentrationPm2p5, 2, 0, 0); 
        spr.pushSprite(90, 110);
        spr.deleteSprite();

      //sprite buffer for pm4p0
        spr.createSprite(70, 40);
        spr.fillSprite(TFT_BLACK);
        spr.setFreeFont(&FreeMonoBold12pt7b);
        if(massConcentrationPm1p0<=15)
          spr.setTextColor(TFT_GREEN);
        else
          spr.setTextColor(TFT_RED);
        spr.drawFloat(massConcentrationPm4p0, 2, 0, 0); 
        spr.pushSprite(90, 160);
        spr.deleteSprite();

      //sprite buffer for pm10p0
        spr.createSprite(70, 40);
        spr.fillSprite(TFT_BLACK);
        spr.setFreeFont(&FreeMonoBold12pt7b);
        if(massConcentrationPm1p0<=15)
          spr.setTextColor(TFT_GREEN);
        else
          spr.setTextColor(TFT_RED);
        spr.drawFloat(massConcentrationPm10p0, 2, 0, 0); 
        spr.pushSprite(90, 210);
        spr.deleteSprite();
}
    // Send value to SEN50 virtual pins
    Blynk.virtualWrite(V0, massConcentrationPm1p0);
    Blynk.virtualWrite(V1, massConcentrationPm2p5);
    Blynk.virtualWrite(V2, massConcentrationPm4p0);
    Blynk.virtualWrite(V3, massConcentrationPm10p0);


  // Read BMP280 values: (for now we only have 1 sensor)
  float BMP280_1_Temperature; // pressure sensor 1 values (before filter)
  float BMP280_1_Pressure = bmp1.readPressure();
  float BMP280_1_Altitude;
  float BMP280_2_Temperature; // pressure sensor 2 values (after filter)
  float BMP280_2_Pressure = bmp2.readPressure();
  float BMP280_2_Altitude;
  float BMP280_Pressure_Difference = abs(BMP280_1_Pressure - BMP280_2_Pressure);

  // TO-DO: proper error handling function:

  // Show values in serial monitor:
  Serial.print(F("Temperature 1 = "));
  Serial.print(bmp1.readTemperature());
  Serial.print(" *C");
  Serial.print("\t");
  Serial.print(F("Pressure 1 = "));
  Serial.print(bmp1.readPressure());
  Serial.print(" Pa");
  Serial.print("\t");
  Serial.print(F("Approx altitude 1 = "));
  Serial.print(bmp1.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.print(" m");
  Serial.print("\t");
  Serial.println();

  delay(100);

  Serial.print(F("Temperature 2 = "));
  Serial.print(bmp2.readTemperature());
  Serial.print(" *C");
  Serial.print("\t");
  Serial.print(F("Pressure 2 = "));
  Serial.print(bmp2.readPressure());
  Serial.print(" Pa");
  Serial.print("\t");
  Serial.print(F("Approx altitude 2 = "));
  Serial.print(bmp2.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.print(" m");
  Serial.print("\t");
  Serial.println();

  delay(100);

  Serial.print(F("Pressure DIFFERENCE = "));
  Serial.print(BMP280_Pressure_Difference);
  Serial.println();

  delay(1000);

  //Sprite buffer for Pressure 1 value:
  spr.createSprite(150, 20);
  spr.fillSprite(TFT_BLACK);
  spr.setFreeFont(&FreeMonoBold12pt7b);
  if(BMP280_1_Pressure>=101325)
    spr.setTextColor(TFT_GREEN);
  else
    spr.setTextColor(TFT_YELLOW);
  spr.drawFloat(BMP280_1_Pressure, 2, 0, 0); //display number
  spr.pushSprite(190, 85); //push to LCD
  spr.deleteSprite(); //clear buffer

  //Sprite buffer for Pressure 2 value:
  spr.createSprite(150, 20);
  spr.fillSprite(TFT_BLACK);
  spr.setFreeFont(&FreeMonoBold12pt7b);
  if(BMP280_2_Pressure>=101325)
    spr.setTextColor(TFT_GREEN);
  else
    spr.setTextColor(TFT_YELLOW);
  spr.drawFloat(BMP280_2_Pressure, 2, 0, 0); //display number
  spr.pushSprite(190, 145); //push to LCD
  spr.deleteSprite(); //clear buffer

  //Sprite buffer for Pressure Difference value:
  spr.createSprite(150, 20);
  spr.fillSprite(TFT_BLACK);
  spr.setFreeFont(&FreeMonoBold12pt7b);
  if(BMP280_1_Pressure>=101325)
    spr.setTextColor(TFT_GREEN);
  else
    spr.setTextColor(TFT_YELLOW);
  spr.drawFloat(BMP280_Pressure_Difference, 2, 0, 0); //display number
  spr.pushSprite(190, 210); //push to LCD
  spr.deleteSprite(); //clear buffer

  // Send value to virtual pins (NOT SURE WHAT THIS FUNCTION DOES.. CHECK LATER)
  Blynk.virtualWrite(V4, BMP280_1_Pressure);
  Blynk.virtualWrite(V5, BMP280_2_Pressure);

}

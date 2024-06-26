# ABOUT #
For running Seeeduino Wio Terminal with these sensors:
- PM2.5 sensor: Sensirion SEN50
- Pressure sensors x2: BMP280

*Proper housekeeping will be done (proper folder struct etc.) near the end of this proj. Everything will possibly be uploaded to a different repo.*

--
# IMPORTANT #
Latest test code is in this file: [blynk_wio_SEN50/BMP280_2sensors_SPI_Wio_test/*BMP280_2sensors_SPI_Wio_test.ino*](https://github.com/mptsounds/airfilter_wioterminal/blob/3b7e96e41223d983c9aca6e93e53a8fa2b6ff305/blynk_wio_SEN50/BMP280_2sensors_SPI_Wio_test/BMP280_2sensors_SPI_Wio_test.ino)

--
# RESOURCES #
Blynk:		 https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk

Wio Terminal:	 https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/

SEN50:		 https://github.com/Sensirion/arduino-i2c-sen5x
***Download "Sensiron Core" library and paste into "...\Documents\Arduino\libraries" (for using SEN50)

  SEN50 catalogue:	 https://sensirion.com/products/catalog/SEN50/

BMP280:		 https://github.com/adafruit/Adafruit_BMP280_Library

--

--

--

--
# ========== work in progress ========== #

--
# USAGE INSTRUCTIONS (Under construction)#
To compile & upload blynk_wio_SEN50.ino from a new PC:

1. Install Arduino

2. Set up Arduino to recognise Wio Terminal (follow instructions in the link for Wio Terminal in RESOURCES section)

3. Tools >> Manage Libraries >> Install the following (with dependencies):
   (ignore for the libraries you already installed)
   - Adafruit BusIO
   - Adafruit GFX Library (for the fonts)
   - Blynk
   - Seeed Arduino rpcUnified (for the rpcWiFi lib)
   - Sensirion I2C SEN5X (for PM2.5 sensor)

4. Install additional libraries:
   - Sensirion Core (for PM2.5 sensor, from the SEN50 GitHub link)
   - Blynk libraries (follow the instructions in the link for Blynk in RESOURCES section)
   - Adafruit BMP 

5. Update wifi name & password in blynk_wio_SEN50.ino (line 24 & 25, starting with "char ssid[]")

6. Verify code & troubleshoot.
   - If there's an error related to Free_Fonts.h: copy the Free_Fonts.h file to the same location as blynk_wio_SEN50.ino --> open it in a new Arduino tab --> Verify
   - If there're errors related to Blynk.cloud, check if the device is recognised (follow the instructions in the link for Blynk in RESOURCES section)
   - If you get a "Multiple libraries were found for "TFT_eSPI.h"" error, follow the steps outlined here: https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/#library-file-name-conflicts

7. Upload code to Wio Terminal.
   - If upload fails or there's no response, try uploading the basic Arduino Sample Script: File >> Examples >> 01.Basics >> Blink
   - Make sure you chose the correct port

--

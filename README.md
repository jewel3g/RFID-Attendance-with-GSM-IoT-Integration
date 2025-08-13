# RFID-Attendance-with-GSM-IoT-Integration


Hardware:

Arduino Uno (or compatible)

MFRC522 RFID module connected via SPI (Pins: SS=10, RST=9)

16x2 LCD connected (pins 7,6,5,4,3,2)

GSM Module SIM800/900 connected via SoftwareSerial (pins 7 RX, 8 TX)

RTC module DS1307 (I2C) for time

Buttons connected on analog pins A0..A3 (as in your original code)

LED on pin 8

Library 
1. LiquidCrystal
Official Arduino library for controlling LCDs.

GitHub (Arduino official repo):
https://github.com/arduino-libraries/LiquidCrystal

2. EEPROM
Arduino core library to read/write EEPROM memory.

GitHub (Arduino core repo):
https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/EEPROM

3. SPI
Standard Arduino SPI communication library.

GitHub (Arduino core repo):
https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/SPI

4. MFRC522
RFID module library for MFRC522 reader.

Popular GitHub repo:
https://github.com/miguelbalboa/rfid

5. Wire
Arduino I2C library for communication with I2C devices (like RTC).

GitHub (Arduino core repo):
https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/Wire

6. TimeLib
Library to handle time and date easily.

GitHub repo:
https://github.com/PaulStoffregen/Time

7. DS1307RTC
Library to interface with DS1307 RTC chip.

Often used as part of the Time library family, also found here:
https://github.com/PaulStoffregen/DS1307RTC

Firebase:

Create a Firebase Realtime Database

Get your database URL, e.g., yourproject.firebaseio.com

Set rules temporarily to allow write without authentication (for testing):


The RFID scan checks if the card matches known UIDs.

Attendance count is stored in EEPROM and displayed on LCD.

After storing locally, the count is sent to Firebase via GPRS (GSM).

GSM is controlled with AT commands using SoftwareSerial.

The JSON sent is like: {"Boby":5}, so each user's count updates the Firebase DB.

You can view attendance data live on Firebase console or via your app.

Final notes
Make sure your GSM module’s serial pins don’t conflict with LCD pins (change pins if needed).

Test GSM commands manually first on serial monitor to confirm your module connects to GPRS.

Adjust delays and add robust error checking as needed.

Secure your Firebase with auth tokens before production.


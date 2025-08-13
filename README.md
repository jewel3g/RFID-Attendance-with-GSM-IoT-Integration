# RFID-Attendance-with-GSM-IoT-Integration


Hardware:

Arduino Uno (or compatible)

MFRC522 RFID module connected via SPI (Pins: SS=10, RST=9)

16x2 LCD connected (pins 7,6,5,4,3,2)

GSM Module SIM800/900 connected via SoftwareSerial (pins 7 RX, 8 TX)

RTC module DS1307 (I2C) for time

Buttons connected on analog pins A0..A3 (as in your original code)

LED on pin 8

Firebase:

Create a Firebase Realtime Database

Get your database URL, e.g., yourproject.firebaseio.com

Set rules temporarily to allow write without authentication (for testing):

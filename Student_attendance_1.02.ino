//-------------------------Program developed by MD.BAHAUDDIN BOBY------------------//
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
const int rs = 7;
const int en = 6;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const int LED = 8;
boolean ok = false;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int list = A0;
const int CLM = A1;
const int yes = A2;
const int no = A3;
int H = 0;
int M = 0;
int S = 0;
int i = 0;
int ID1 = 0;
int ID2 = 0;
int ID3 = 0;
int ID4 = 0;
int ID5 = 0;
int ID6 = 0;
int ID7 = 0;
int ID8 = 0;
int ID9 = 0;
int ID10 = 0;
int ID11 = 0;
int ID12 = 0;
char UID[] = "";
// **************************** SETTINGS ************************ //
// ------ From -------- //  (Set the time range for attendance in hours 0 to 23)
int h = 01; // Hrs
int m = 00; // Min
// ------- To ------- //
int h1 = 21; // Hrs
int m1 = 50; //Min
// ---------------- SET UIDs ----------------- //
char UID1[] = "12:5D:CC:2F";
char UID2[] = "11:36:4C:73";
char UID3[] = "07:F9:39:27";
char UID4[] = "57:29:BB:26";
char UID5[] = "B7:1F:AC:26";
char UID6[] = "45:8A:AF:C0";
char UID7[] = "15:9F:A4:C0";
char UID8[] = "55:CB:AF:C0";
char UID9[] = "65:7D:AF:C0";
char UID10[] = "05:2C:AA:04";
char UID11[] = "55:7D:AA:04";
char UID12[] = "BD:8A:16:0B";
// -------------- NAMES -----------------------//
char Name1[] = "Boby";
char Name2[] = "Mahabubr";
char Name3[] = "Azad";
char Name4[] = "Haris";
char Name5[] = "Salim";      
char Name6[] = "Student6";
char Name7[] = "Student7";
char Name8[] = "Student8";
char Name9[] = "Student9";
char Name10[] = "Student10";
char Name11[] = "Student11";
char Name12[] = "Student12";
// ********************************************************** //
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(yes, INPUT);
  pinMode(no, INPUT);
  pinMode(list, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(CLM, INPUT);
  digitalWrite(CLM, HIGH);
  digitalWrite(LED, LOW);
  digitalWrite(yes, HIGH);
  digitalWrite(no, HIGH);
  digitalWrite(list, HIGH);
}
void loop()
{
  if (digitalRead(list) == LOW)
  {
    Read_data();
  }
  if (digitalRead(CLM) == LOW)
  {
    clear_Memory();
  }
  tmElements_t tm;
  if (RTC.read(tm))
  {
    lcd.clear();
    H = tm.Hour;
    M = tm.Minute;
    S = tm.Second;
    lcd.setCursor(0, 0);
    lcd.print("TIME:");
    lcd.print(tm.Hour);
    lcd.print(":");
    lcd.print(tm.Minute);
    lcd.print(":");
    lcd.print(tm.Second);
    lcd.setCursor(0, 1);
    lcd.print("DATE:");
    lcd.print(tm.Day);
    lcd.print("/");
    lcd.print(tm.Month);
    lcd.print("/");
    lcd.print(tmYearToCalendar(tm.Year));
    delay(1000);
  } else {
    if (RTC.chipPresent())
    {
      lcd.setCursor(0, 0);
      lcd.print("RTC stopped!!!");
      lcd.setCursor(0, 1);
      lcd.print("Run SetTime code");
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Read error!");
      lcd.setCursor(0, 1);
      lcd.print("Check circuitry!");
    }
  }
  if (H >= h)
  {
    if (M >= m)
    {
      ok = true;
    }
  }
  if (H == h1)
  {
    if (M == m1)
    {
      ok = false;
    }
  }
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K)
  {
    Serial.println(F("Your tag is not of type MIFARE Classic, your card/tag can't be read :("));
  }
  String StrID = "" ;
  for (byte i = 0; i < 4; i ++)
  {
    StrID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "" );
  }
  StrID.toUpperCase();
  if (ok == false)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Attendance is");
    lcd.setCursor(0, 1);
    lcd.print("Closed.");
    delay(1000);
  }
  if (ok)
  {
    //-----------------------------------//
    if (StrID == UID1)
    {
      ID1 = EEPROM.read(1);
      ID1 = ID1 + 1;
      if (ID1 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID1 != 256)
      {
        EEPROM.write(1, ID1);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID2)
    {
      ID2 = EEPROM.read(2);
      ID2 = ID2 + 1;
      if (ID2 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID2 != 256)
      {
        EEPROM.write(2, ID2);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID3)
    {
      ID3 = EEPROM.read(3);
      ID3 = ID3 + 1;
      if (ID3 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID3 != 256)
      {
        EEPROM.write(3, ID3);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID4)
    {
      ID4 = EEPROM.read(4);
      ID4 = ID4 + 1;
      if (ID4 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID4 != 256)
      {
        EEPROM.write(4, ID4);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID5)
    {
      ID5 = EEPROM.read(5);
      ID5 = ID5 + 1;
      if (ID5 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID5 != 256)
      {
        EEPROM.write(5, ID5);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID6)
    {
      ID6 = EEPROM.read(6);
      ID6 = ID6 + 1;
      if (ID6 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID6 != 256)
      {
        EEPROM.write(6, ID6);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID7)
    {
      ID7 = EEPROM.read(7);
      ID7 = ID7 + 1;
      if (ID7 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID7 != 256)
      {
        EEPROM.write(7, ID7);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID8)
    {
      ID8 = EEPROM.read(8);
      ID8 = ID1 + 1;
      if (ID8 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID8 != 256)
      {
        EEPROM.write(8, ID8);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID9)
    {
      ID9 = EEPROM.read(9);
      ID9 = ID9 + 1;
      if (ID9 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID9 != 256)
      {
        EEPROM.write(9, ID9);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID10)
    {
      ID10 = EEPROM.read(10);
      ID10 = ID10 + 1;
      if (ID10 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID10 != 256)
      {
        EEPROM.write(10, ID10);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID11)
    {
      ID11 = EEPROM.read(11);
      ID11 = ID11 + 1;
      if (ID11 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID11 != 256)
      {
        EEPROM.write(11, ID11);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    //-----------------------------------//
    if (StrID == UID12)
    {
      ID12 = EEPROM.read(12);
      ID12 = ID12 + 1;
      if (ID12 == 256)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Memory is Full");
        lcd.setCursor(0, 1);
        lcd.print("Please Clear All.");
        for (i = 0; i < 20; i++)
        {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
        }
        i = 0;
        return;
      }
      if (ID12 != 256)
      {
        EEPROM.write(12, ID12);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Attendance");
        lcd.setCursor(0, 1);
        lcd.print("Registered !!!");
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        return;
      }
    }
    if (StrID != UID1 || StrID != UID2 || StrID != UID3 || StrID != UID4
        || StrID != UID5 || StrID != UID6 || StrID != UID7 || StrID != UID8
        || StrID != UID9 || StrID != UID10 || StrID != UID11 || StrID != UID12)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Unknown RFID");
      lcd.setCursor(0, 1);
      lcd.print("Card !!!");
      for (i = 0; i < 3; i++)
      {
        digitalWrite(LED, HIGH);
        delay(200);
        digitalWrite(LED, LOW);
        delay(200);
      }
    }
    rfid.PICC_HaltA ();
    rfid.PCD_StopCrypto1();
  }
}
void Read_data()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Name1);
  lcd.print(":");
  lcd.print(EEPROM.read(1));
  lcd.setCursor(0, 1);
  lcd.print(Name2);
  lcd.print(":");
  lcd.print(EEPROM.read(2));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Name3);
  lcd.print(":");
  lcd.print(EEPROM.read(3));
  lcd.setCursor(0, 1);
  lcd.print(Name4);
  lcd.print(":");
  lcd.print(EEPROM.read(4));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Name5);
  lcd.print(":");
  lcd.print(EEPROM.read(5));
  lcd.setCursor(0, 1);
  lcd.print(Name6);
  lcd.print(":");
  lcd.print(EEPROM.read(6));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Name7);
  lcd.print(":");
  lcd.print(EEPROM.read(7));
  lcd.setCursor(0, 1);
  lcd.print(Name8);
  lcd.print(":");
  lcd.print(EEPROM.read(8));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Name9);
  lcd.print(":");
  lcd.print(EEPROM.read(9));
  lcd.setCursor(0, 1);
  lcd.print(Name10);
  lcd.print(":");
  lcd.print(EEPROM.read(10));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Name11);
  lcd.print(":");
  lcd.print(EEPROM.read(11));
  lcd.setCursor(0, 1);
  lcd.print(Name12);
  lcd.print(":");
  lcd.print(EEPROM.read(12));
  delay(2000);
}
void clear_Memory()
{
  lcd.clear();
  lcd.print(0, 0);
  lcd.print(F("Clear All Data?"));
  lcd.setCursor(0, 1);
  lcd.print(F("Long press: Y/N"));
  delay(2500);
  Serial.print("YES");
  if (digitalRead(yes) == LOW)
  {
    EEPROM.write(1, 0);
    EEPROM.write(2, 0);
    EEPROM.write(3, 0);
    EEPROM.write(4, 0);
    EEPROM.write(5, 0);
    EEPROM.write(6, 0);
    EEPROM.write(7, 0);
    EEPROM.write(8, 0);
    EEPROM.write(9, 0);
    EEPROM.write(10, 0);
    EEPROM.write(11, 0);
    EEPROM.write(12, 0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("All Data Cleared"));
    lcd.setCursor(0, 1);
    lcd.print(F("****************"));
    delay(1500);
  }
  if (digitalRead(no) == LOW);
  {
    return;
  }
}

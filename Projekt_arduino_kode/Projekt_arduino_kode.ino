#include <Arduino.h>
#include <SPI.h>
#include <SomeSerial.h>
#include <Adafruit_ATParser.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BLEBattery.h>
#include <Adafruit_BLEEddystone.h>
#include <Adafruit_BLEGatt.h>
#include <Adafruit_BLEMIDI.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>
#include <Servo.h>

#include "BluefruitConfig.h"
#include "pitches.h"


#define FACTORYRESET_ENABLE 0
#define MINIMUM_FIRMWARE_VERSION "0.6.6"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

String passKode = "1207";

const int buzzerPin = 9;

const int servoPin = 3;

Servo lockMechanism;

void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

void setup(void) {
  // put your setup code here, to run once:
  while (!Serial);
  delay(500);

  Serial.begin(115200);
  Serial.println(F("Intilasing module"));
  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Bluefruit not available"));
  }
  Serial.println( F("OK!") );

  //disable echo from bluefruit
  ble.echo(false);

  //verbose is set to false to avoid getting debug info
  ble.verbose(false);

  //Module named
  ble.println("AT+GAPDEVNAME=Testvej 1");

  //Wait for the module to respond
  ble.waitForOK();
  while (! ble.isConnected()) {
    delay(500);
  }

  // Set module to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  lockMechanism.attach(servoPin);

  pinMode(buzzerPin, OUTPUT);

}
String brugerKode = "";
int antalTries = 0;
void loop(void) {

  while (Serial.available()) {

    int d = Serial.read();
    brugerKode += (char)d;
    if (brugerKode.length() == 4) {
      Serial.println(brugerKode);
      if (brugerKode == passKode) {

        Serial.println("Kode korrekt");

        brugerKode = "";

        song();

        lockMechanism.write(0);
        lockMechanism.write(90);
        lockMechanism.write(180);

        delay(1000);

        lockMechanism.write(90);
        lockMechanism.write(0);

      }
      if (brugerKode != passKode || brugerKode != "") {
        antalTries++;
        brugerKode = "";
        if (antalTries == 3) {
          Serial.print("Kontakt administrator.");
          antalTries = 0;
        }
      }
    }


  }
  delay(1000);
  brugerKode = "";
}

void note(int sound, int duration) {
  tone(buzzerPin, sound, duration);

}

void song() {
  note(NOTE_G4, 250);
  delay(500);
  note(NOTE_G4, 250);
  delay(500);
  note(NOTE_F4, 250);
  delay(500);
  note(NOTE_F4, 250);
  delay(250);
  note(NOTE_G4, 250);
  delay(250);
  note(NOTE_G4, 750);
  note(NOTE_G4, 250);
  delay(500);
  note(NOTE_F4, 250);
  delay(250);
  note(NOTE_C4, 500);
  note(NOTE_C4, 500);
  note(NOTE_C4, 1250);

  delay(500);

  note(NOTE_G4, 250);
  delay(500);
  note(NOTE_G4, 250);
  delay(500);
  note(NOTE_F4, 250);
  delay(500);
  note(NOTE_F4, 250);
  delay(250);
  note(NOTE_G4, 250);
  delay(250);
  note(NOTE_G4, 750);
  note(NOTE_G4, 250);
  delay(500);
  note(NOTE_F4, 250);
  delay(250);
  note(NOTE_C4, 500);
  note(NOTE_C4, 500);
  note(NOTE_C4, 1250);

  delay(500);

  note(NOTE_G4, 250);
  delay(500);
  note(NOTE_G4, 250);
  delay(500);
  note(NOTE_F4, 250);
  delay(500);
  note(NOTE_F4, 250);
  delay(250);
  note(NOTE_G4, 250);
  delay(250);
  note(NOTE_G4, 750);
  note(NOTE_G4, 250);
  delay(500);
  note(NOTE_F4, 250);
  delay(250);
  note(NOTE_C4, 500);
  note(NOTE_C4, 500);
  note(NOTE_C4, 1250);

  delay(500);

  note(NOTE_F5, 250);
  delay(500);
  note(NOTE_F5, 250);
  delay(500);
  note(NOTE_F5, 250);
  delay(500);
  note(NOTE_F5, 250);
  delay(500);
  note(NOTE_C5, 500);
  delay(500);
  note(NOTE_F4, 250);
  delay(500);
  note(NOTE_C4, 250);
  delay(250);
  note(NOTE_C4, 750);
  note(NOTE_E4, 250);
  delay(250);
  note(NOTE_C4, 1250);

}

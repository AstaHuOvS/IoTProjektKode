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

#include "BluefruitConfig.h"


%define FACTORYRESET_ENABLE 0
#define MINIMUM_FIRMWARE_VERSION "0.6.6"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


void setup() {
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
  ble.println("AT+GAPDEVNAME=Testvej 01");
  
  //Wait for the module to respond
  ble.waitForOK();
  while (! ble.isConnected()) {
    delay(500);
  }
  
  // Set module to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

}

void loop() {
  // put your main code here, to run repeatedly:
  














}

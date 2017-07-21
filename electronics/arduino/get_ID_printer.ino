/*
 * --------------------------------------------------------------------------------------------------------------------
* Intimate Fields reader by Helen J Burgess and Maggie Simon
* Uses a flora board to read from RC522 reader and output to Adafruit thermal printer
* --------------------------------------------------------------------------------------------------------------------
 * Adapted from MFRC522 library: https://github.com/miguelbalboa/rfid
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -------------------------------------
 *             MFRC522      Arduino
 *             Reader/PCD   Uno/101
 * Signal      Pin          Pin/Flora
 * -------------------------------------
 * RST/Reset   RST          9              YELLOW ALLIGATOR
 * SPI SS      SDA(SS)      10             BLUE ALLIGATOR
 * SPI MOSI    MOSI         11 / ICSP-4    GREEN JUMPER
 * SPI MISO    MISO         12 / ICSP-1    BROWN JUMPER
 * SPI SCK     SCK          13 / ICSP-3    ORANGE JUMPER
 */
#include "Adafruit_Thermal.h"

#include <SPI.h>
#include <MFRC522.h>

#include "SoftwareSerial.h"
// printer lines. switched on mini and tiny printers so make sure you have them right!
// for "mini" printer, send pin 6 to yellow line (labeled RX) & use yellow clip
// for "tiny" printer, send pin 6 to green line (labeled TX) & use green clip
// on "tiny" printer, ground cable is red. on "mini", it's black. 
#define TX_PIN 6 // Arduino transmit  GREEN ALLIGATOR
#define RX_PIN 12 // Arduino receive   *** don't use on 3.3v systems

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

// from reader
#define RST_PIN         9          // Configurable, Yellow Alligator
#define SS_PIN          10         // Configurable, Blue Alligator

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
	mySerial.begin(9600);		// Initialize serial communications with the PC
	while (!mySerial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	printer.begin();        // Init printer (same regardless of serial type)
  mfrc522.PCD_Init();		// Init MFRC522
  printer.println(F("Touch a ring to the pad to get a secret message"));
  printer.feed(2);
}

/**
 * testing stuff
 */
 void loop() {
  // Look for new cards
  if(mfrc522.PICC_IsNewCardPresent()) {
    unsigned long uid = getID();
    //Check if card is valid
    if(uid != -1){
      if(uid == 1111111111){
      printer.println("replace the ID number above and put your posie text here"); 
      }      
      else if(uid == 2222222222){
      printer.println("use \n to add a new line");
      }
      else if(uid == 3333333333){
      printer.println("keep adding more posies by copying and pasting this else if statement");
      }  
      else {
      //If not one of the above IDs, print the ID
      printer.println("Empty card detected, UID: ");
      printer.println(uid);
     }
   printer.feed(4);
   }
  }
 }

unsigned long getID(){
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return -1;
  }
  unsigned long hex_num;
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  return hex_num;
}

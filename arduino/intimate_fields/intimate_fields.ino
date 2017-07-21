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
  mySerial.begin(9600);   // Initialize serial communications with the PC
  while (!mySerial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  printer.begin();        // Init printer (same regardless of serial type)
  mfrc522.PCD_Init();   // Init MFRC522
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
      if(uid == 4294945440){
      printer.println("A posie shewing man and wife to be one:\nFlesh of my flesh,\n   bone of my bone,\nFrome one made two,\n   is two made one."); 
      }      
      else if(uid == 4294958406){
      printer.println("Intimate Fields\n\nA Kit by Helen J Burgess\n and Margaret Simon");
      } 
      else if(uid == 4294942368){
      printer.println("Intimate Fields\n\nA Kit by Helen J Burgess\n and Margaret Simon");
      } 
      else if(uid == 8743){
      printer.println("A neglected lover to his mistresse:\nTis true as old,\n   hot love, soon cold.");
      } 
      else if(uid == 4294937866){
      printer.println("Loves Garland:\n Read, Skanne, Judge");
      }           
      else if(uid == 4294938122){
      printer.println("Every secret has its little casket\n -- Gaston Bachelard");
      }  
      else if(uid == 4294957818){
      printer.println("A posie in a Ring:\nRemember this, and give a kisse.");
      }  
      else if(uid == 4294937594){
      printer.println("A posie in a Ring:\nThy love I crave, mine shalt thou have.");
      }   
      else if(uid == 4294941450){
      printer.println("A posie in a Ring:\nThine mine, mine thine.");
      }  
      else if(uid == 4294938634){
      printer.println("A posie in a Ring:\nA happy breast, Where love doth rest.");
      }  
      else if(uid == 4294938890){
      printer.println("A posie in a Ring:\nIn thee a flame, in me the same.");
      }  
      else if(uid == 4294951298){
      printer.println("A posie in a Ring:\nGod above, increase our Love.");
      }  
      else if(uid == 4294955650){
      printer.println("A posie in a Ring:\nHearts content can nere repent.");
      }  
       else if(uid == 4294961282){
      printer.println("A posie in a Ring:\nAs true to me, as I to thee.");
      }  
       else if(uid == 4294963074){
      printer.println("A posie in a Ring:\nNot two, but one, till life be gone.");
      }  
       else if(uid == 4294938890){
      printer.println("A posie in a Ring:\nThe Loadstone of love, is love.");
      }  
       else if(uid == 4294942730){
      printer.println("A posie in a Ring:\nDesire hath no rest.");
      }  
      else if(uid == 4294958150){
      printer.println("Loves Garland:\n Read, Skanne, Judge.");
      }  
      else if(uid == 4294942880){
      printer.println("Two hands, two feete,\nTwo eares, two eyes;\nOne tongue, one heart,\nWhere true Love lies.");
      }  
       else if(uid == 4294942624){
      printer.println("The Posie of a Handkerchief from a young man to his Love.\nLove is a chaine,\n   whole links of Gold,\nTwo hearts within,\n   one bosome hold.");
      }   
      else {
      //Print UID to serial for logging
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
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

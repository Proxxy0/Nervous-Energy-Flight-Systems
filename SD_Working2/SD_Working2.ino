
/*
 SD card read/write - modified by Bill Greiman for SdFat

This example shows how to read and write data to and from an SD card file   
The circuit:
* SD card attached to SPI bus as follows:
** MOSI - pin 11
** MISO - pin 12
** CLK - pin 13
** CS - pin 4

created   Nov 2010
by David A. Mellis
updated 2 Dec 2010
by Tom Igoe
modified by Bill Greiman 11 Apr 2011
This example code is in the public domain.
   
*/
#include <SdFat.h>
#include <SPI.h>
SdFat sd;
SdFile myFile;

// On the Ethernet Shield, CS is pin 4. SdFat handles setting SS 
const int chipSelect = 8;

void setup() {
 Serial.begin(9600);
 
 // Initialize SdFat or print a detailed error message and halt
 // Use half speed like native library.  
 // change to SPI_FULL_SPEED for more performance.
 if (!sd.init(SPI_HALF_SPEED, chipSelect)) sd.initErrorHalt();
 
 // open the file for write at end like the Native SD library
 if (!myFile.open("test.txt", O_WRITE | O_CREAT | O_APPEND)) {
   sd.errorHalt("error opening test.txt for write");
 } 
 // if the file opened okay, write to it:
 Serial.print("Writing to test.txt...");
 myFile.println("testing 1, 2, 3.");
 
 // close the file:
 myFile.close();
 Serial.println("done.");

 // re-open the file for reading:
 if (!myFile.open("test.txt", O_READ)) {
   sd.errorHalt("error opening test.txt for read");
 } 
 Serial.println("test.txt:");
   
 // read from the file until there's nothing else in it:
 int data;
 while ((data = myFile.read()) >= 0) Serial.write(data);
 // close the file:
 myFile.close();
}

void loop() {
  // nothing happens after setup
}

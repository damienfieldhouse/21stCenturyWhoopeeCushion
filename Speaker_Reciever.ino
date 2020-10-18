//______________________________________________________Speakers
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
bool pause = 1; //pause = 1 unpause = 0
int track = 0;
int trackCheck = 0;
SoftwareSerial mySoftwareSerial(9, 10); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//______________________________________________________Radio
#include <SPI.h>
#include <RF24Network.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)

void setup()
{
  delay(2000);
  Serial.begin(115200);

//______________________________________________________Speakers
  mySoftwareSerial.begin(9600);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

//______________________________________________________Radio
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
}

void loop()
{
//______________________________________________________Speakers
if (track == 0){
  trackCheck = 0;
  }

if (track != trackCheck && track != 0){
//  myDFPlayer.play(track);  //Play the mp3
      if (track >= 1 && track <= 12){
      delay(50);
      myDFPlayer.playFolder(01, track);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
      }
      if (track >= 13 && track <= 22){
      delay(50);
      myDFPlayer.playFolder(02, track);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
      }
      if (track >= 23 && track <= 32){
      delay(50);
      myDFPlayer.playFolder(03, track);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
      }
      if (track >= 33 && track <= 45){
      delay(50);
      myDFPlayer.playFolder(04, track);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
      }
      if (track >= 46 && track <= 55){
      delay(50);
      myDFPlayer.playFolder(05, track);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
      }
  trackCheck = track;
  }

//______________________________________________________Radio
  network.update();
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    network.read(header, &track, sizeof(track)); // Read the incoming data
  Serial.println(track);
  }
//______________________________________________________Debugging


}

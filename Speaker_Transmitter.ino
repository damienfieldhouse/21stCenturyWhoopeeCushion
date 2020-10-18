//______________________________________________________Speakers
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
bool pause = 1; //pause = 1 unpause = 0
int track = 0;
int trackCheck = 0;
int randomTrackGenerated = 0;
long timeSinceButtonPressed = 0;
SoftwareSerial mySoftwareSerial(9, 10); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//______________________________________________________Radio
#include <SPI.h>
#include <RF24Network.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01; 

//______________________________________________________Buttons
const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;
const int button5Pin = 6;
const int potPin = A1;
int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;
int button5State = 0;
int potValue = 0;
int volume = 0;

void setup() {
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

  myDFPlayer.volume(20);  //Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

//______________________________________________________Radio
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  
//______________________________________________________Buttons
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  pinMode(button5Pin, INPUT);

}

void loop() {
//______________________________________________________Speakers
  myDFPlayer.volume(volume);


//______________________________________________________Radio
//    network.update();
//    RF24NetworkHeader header(node01);     // (Address where the data is going)
//    bool ok = network.write(header, &track, sizeof(track)); // Send the data

//______________________________________________________Buttons and Radio
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  button4State = digitalRead(button4Pin);
  button5State = digitalRead(button5Pin);
  potValue = analogRead(potPin);
  volume = map(potValue, 10, 1000, 0, 30);
  if (button1State == LOW && button2State == LOW && button3State == LOW && button4State == LOW && button5State == LOW && track != 0) {
    track = 0;
    randomTrackGenerated = 0;
    network.update();
    RF24NetworkHeader header(node01);     // (Address where the data is going)
    bool ok = network.write(header, &track, sizeof(track)); // Send the data
  }

  if (button1State == HIGH && randomTrackGenerated == 0) {
    track = random(1, 13);
    randomTrackGenerated = 1;
  }
  if (button1State == HIGH && randomTrackGenerated == 1) {
    network.update();
    RF24NetworkHeader header(node01);     // (Address where the data is going)
    bool ok = network.write(header, &track, sizeof(track)); // Send the data
    delay(50);
    myDFPlayer.playFolder(01, track);
    delay(1000);
  }
  
  if (button2State == HIGH && randomTrackGenerated == 0) {
    track = random(13, 23);
    randomTrackGenerated = 2;
  }
  if (button2State == HIGH && randomTrackGenerated == 2) {
    network.update();
    RF24NetworkHeader header(node01);     // (Address where the data is going)
    bool ok = network.write(header, &track, sizeof(track)); // Send the data
    delay(50);
    myDFPlayer.playFolder(02, track);
    delay(1000);
  }
  
  if (button3State == HIGH && randomTrackGenerated == 0) {
    track = random(23, 33);
    randomTrackGenerated = 3;
  }
  if (button3State == HIGH && randomTrackGenerated == 3) {
    network.update();
    RF24NetworkHeader header(node01);     // (Address where the data is going)
    bool ok = network.write(header, &track, sizeof(track)); // Send the data
    delay(50);
    myDFPlayer.playFolder(03, track);
    delay(1000);
  }
  
  if (button4State == HIGH && randomTrackGenerated == 0) {
    track = random(33, 46);
    randomTrackGenerated = 4;
  }
  if (button4State == HIGH && randomTrackGenerated == 4) {
    network.update();
    RF24NetworkHeader header(node01);     // (Address where the data is going)
    bool ok = network.write(header, &track, sizeof(track)); // Send the data
    delay(50);
    myDFPlayer.playFolder(04, track);
    delay(1000);
  }
  
  if (button5State == HIGH && randomTrackGenerated == 0) {
    track = random(46, 56);
    randomTrackGenerated = 5;
  }
  if (button5State == HIGH && randomTrackGenerated == 5) {
    network.update();
    RF24NetworkHeader header(node01);     // (Address where the data is going)
    bool ok = network.write(header, &track, sizeof(track)); // Send the data
    delay(50);
    myDFPlayer.playFolder(05, track);
    delay(1000);
  }

//______________________________________________________Debugging

  Serial.println(button2State);
}

#include <Arduino.h>
#include <DFPlayerMini_Fast.h>
#include <SoftwareSerial.h>
#include <LedControl.h>

#define LEFT_LEFT 2
#define LEFT_RIGHT 3
#define RIGHT_LEFT 6
#define RIGHT_RIGHT 8

#define INST_ONE 12
#define INST_TWO 13

SoftwareSerial mp3Serial(10, 11);
DFPlayerMini_Fast myDFPlayer;

 //pin 12 is connected to the DataIn 
 //pin 11 is connected to the CLK 
 //pin 10 is connected to LOAD 
LedControl lc = LedControl(A2,A0,A1,1);

void setup() {
  mp3Serial.begin(9600);
  Serial.begin(115200);

  myDFPlayer.begin(mp3Serial, true);
  myDFPlayer.volume(30); 

  myDFPlayer.stop();

  pinMode(LEFT_LEFT, INPUT_PULLUP);
  pinMode(LEFT_RIGHT, INPUT_PULLUP);
  pinMode(RIGHT_LEFT, INPUT_PULLUP);
  pinMode(RIGHT_RIGHT, INPUT_PULLUP);

  pinMode(INST_ONE, INPUT_PULLUP);
  pinMode(INST_TWO, INPUT_PULLUP);

  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);


}


int button[4];

enum INST {
  ROCK_DRUM = 1,
  CLASSIC_DRUM = 5,
  KOREAN = 9,
  SCHOOL = 13
};

void printLight(int* button, INST n) {
  if(button[0]) {
    lc.setLed(0, 0, 3, true);
    lc.setLed(0, 0, 4, true);
    lc.setLed(0, 0, 5, true);
    lc.setLed(0, 0, 6, true);
    lc.setLed(0, 1, 3, true);
    lc.setLed(0, 1, 4, true);
    lc.setLed(0, 1, 5, true);
    lc.setLed(0, 1, 6, true);
  }
  if(button[1]) {
    lc.setLed(0, 2, 3, true);
    lc.setLed(0, 2, 4, true);
    lc.setLed(0, 2, 5, true);
    lc.setLed(0, 2, 6, true);
    lc.setLed(0, 3, 3, true);
    lc.setLed(0, 3, 4, true);
    lc.setLed(0, 3, 5, true);
    lc.setLed(0, 3, 6, true);
  }
  if(button[2]) {
    lc.setLed(0, 4, 3, true);
    lc.setLed(0, 4, 4, true);
    lc.setLed(0, 4, 5, true);
    lc.setLed(0, 4, 6, true);
    lc.setLed(0, 5, 3, true);
    lc.setLed(0, 5, 4, true);
    lc.setLed(0, 5, 5, true);
    lc.setLed(0, 5, 6, true);
  }
  if(button[3]) {
    lc.setLed(0, 6, 3, true);
    lc.setLed(0, 6, 4, true);
    lc.setLed(0, 6, 5, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 3, true);
    lc.setLed(0, 7, 4, true);
    lc.setLed(0, 7, 5, true);
    lc.setLed(0, 7, 6, true);
  }

  switch(n) {
    case 0:
      lc.setLed(0, 0, 0, true);
      break;
    case 1:
      lc.setLed(0, 2, 0, true);
      break;
    case 2:
      lc.setLed(0, 5, 0, true);
      break;
    case 3:
      lc.setLed(0, 7, 0, true);
      break;
  }
}


INST inst = ROCK_DRUM;

INST instNumber;

void loop() {

  instNumber = !digitalRead(INST_ONE) * 2 + !digitalRead(INST_TWO);


  switch(instNumber) {
    case 0:
      inst = ROCK_DRUM;
      break;
    case 1:
      inst = CLASSIC_DRUM;
      break;
    case 2:
      inst = KOREAN;
      break;
    case 3:
      inst = SCHOOL;
      break;
  }

  button[0] = !digitalRead(LEFT_LEFT);
  button[1] = !digitalRead(LEFT_RIGHT);
  button[2] = !digitalRead(RIGHT_LEFT);
  button[3] = !digitalRead(RIGHT_RIGHT);

  lc.clearDisplay(0);
  printLight(button, instNumber);


  if (button[0]) {
    myDFPlayer.play(inst + 0);
    delay(50);
    Serial.println(inst + 0);
  } 
  if (button[1]) {
    myDFPlayer.play(inst + 1);
    delay(50);
    Serial.println(inst + 1);
  } 
   if (button[2]) {
    myDFPlayer.play(inst + 2);
    delay(50);
    Serial.println(inst + 2);
  } 
   if (button[3]) {
    myDFPlayer.play(inst + 3);
    delay(50);
    Serial.println(inst + 3);
  }

  delay(5);
}


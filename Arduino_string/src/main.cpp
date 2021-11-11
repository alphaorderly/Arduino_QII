#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>
#include <Adafruit_VL53L0X.h>


SoftwareSerial mp3Serial(10, 11);
DFPlayerMini_Fast myDFPlayer;
Adafruit_VL53L0X TOF = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;

int distance;

/***** 디파인 *****/
#define PLAYBUTTON  12
#define SHARP       8
#define FLAT        9
#define INST_ONE    6
#define INST_TWO    7

enum instrument {  // 악기 변경용
  OBOE = 1,
  FLUTE = 25,
  TRUMPET = 49, 
  VIOLIN = 73
};

enum pitch {       // 음정 변경용
  DO, DO_SHARP, RE, RE_SHARP, MI, FA, FA_SHARP, SOL, SOL_SHARP, LA, LA_SHARP, TI, 
  HIGH_DO, HIGH_DO_SHARP, HIGH_RE, HIGH_RE_SHARP, HIGH_MI, HIGH_FA, HIGH_FA_SHARP, HIGH_SOL, HIGH_SOL_SHARP, HIGH_LA, HIGH_LA_SHARP, HIGH_TI
};

void setup() {
  mp3Serial.begin(9600);
  Serial.begin(115200);

  if (!TOF.begin()) { 
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  // 핀모드
  pinMode(PLAYBUTTON, INPUT);
  pinMode(SHARP, INPUT);
  pinMode(FLAT, INPUT);
  pinMode(INST_ONE, INPUT);
  pinMode(INST_TWO, INPUT);

  // mp3 초기세팅
  myDFPlayer.begin(mp3Serial, true);
  myDFPlayer.volume(30);                       // 볼륨 20
}

instrument instrumentCode = OBOE; // 기본악기는 오보에로


int distanceCalc(int low, int high) {
  return (low <= distance && distance < high);
}

void playTune(instrument inst, pitch p) {
  myDFPlayer.loop(inst + p);
  while(digitalRead(PLAYBUTTON));
  myDFPlayer.stop();
}

void loop() { 

  int INST = digitalRead(INST_ONE) * 2 + digitalRead(INST_TWO);
  switch(INST) {
    case 0:
      instrumentCode = OBOE;
      break;
    case 1: 
      instrumentCode = FLUTE;
      break;
    case 2:
      instrumentCode = TRUMPET;
      break;
    case 3:
      instrumentCode = VIOLIN;
      break;
  }

    if(digitalRead(PLAYBUTTON)) // 버튼 누르면
    {
      distance = TOF.readRange();
      Serial.println(distance);
      if(!digitalRead(SHARP) && !digitalRead(FLAT)) { // 샾 플랫 안누름
        if(distanceCalc(0, 60)) {
          playTune(instrumentCode, DO);
        } else if (distanceCalc(60, 90)) {
          playTune(instrumentCode, RE);
        } else if (distanceCalc(90, 120)) {
          playTune(instrumentCode, MI);
        } else if (distanceCalc(120, 150)) {
          playTune(instrumentCode, FA);
        } else if (distanceCalc(150, 180)) {
          playTune(instrumentCode, SOL);
        } else if (distanceCalc(180, 210)) {
          playTune(instrumentCode, LA);
        } else if (distanceCalc(210, 240)) {
          playTune(instrumentCode, TI);
        } else if (distanceCalc(240, 270)) {
          playTune(instrumentCode, HIGH_DO);
        } else if (distanceCalc(270, 300)) {
          playTune(instrumentCode, HIGH_RE);
        } else if (distanceCalc(300, 330)) {
          playTune(instrumentCode, HIGH_MI);
        } else if (distanceCalc(330, 360)) {
          playTune(instrumentCode, HIGH_FA);
        } else if (distanceCalc(360, 390)) {
          playTune(instrumentCode, HIGH_SOL);
        } else if (distanceCalc(390, 420)) {
          playTune(instrumentCode, HIGH_LA);
        } else if (distanceCalc(420, 450)) {
          playTune(instrumentCode, HIGH_TI);
        }
      } else if (digitalRead(SHARP) && !digitalRead(FLAT)) { // 샾버튼
          if(distanceCalc(0, 60)) {
          playTune(instrumentCode, DO_SHARP);
        } else if (distanceCalc(60, 90)) {
          playTune(instrumentCode, RE_SHARP);
        } else if (distanceCalc(90, 120)) {
          playTune(instrumentCode, FA);
        } else if (distanceCalc(120, 150)) {
          playTune(instrumentCode, FA_SHARP);
        } else if (distanceCalc(150, 180)) {
          playTune(instrumentCode, SOL_SHARP);
        } else if (distanceCalc(180, 210)) {
          playTune(instrumentCode, LA_SHARP);
        } else if (distanceCalc(210, 240)) {
          playTune(instrumentCode, DO);
        } else if (distanceCalc(240, 270)) {
          playTune(instrumentCode, HIGH_DO_SHARP);
        } else if (distanceCalc(270, 300)) {
          playTune(instrumentCode, HIGH_RE_SHARP);
        } else if (distanceCalc(300, 330)) {
          playTune(instrumentCode, HIGH_FA);
        } else if (distanceCalc(330, 360)) {
          playTune(instrumentCode, HIGH_FA_SHARP);
        } else if (distanceCalc(360, 390)) {
          playTune(instrumentCode, HIGH_SOL_SHARP);
        } else if (distanceCalc(390, 420)) {
          playTune(instrumentCode, HIGH_LA_SHARP);
        } else if (distanceCalc(420, 450)) {
          playTune(instrumentCode, HIGH_TI);
        } 
      } else if (!digitalRead(SHARP) && digitalRead(FLAT)) { // 플랫버튼
          if(distanceCalc(0, 60)) {
          playTune(instrumentCode, DO);
        } else if (distanceCalc(60, 90)) {
          playTune(instrumentCode, DO_SHARP);
        } else if (distanceCalc(90, 120)) {
          playTune(instrumentCode, RE_SHARP);
        } else if (distanceCalc(120, 150)) {
          playTune(instrumentCode, MI);
        } else if (distanceCalc(150, 180)) {
          playTune(instrumentCode, FA_SHARP);
        } else if (distanceCalc(180, 210)) {
          playTune(instrumentCode, SOL_SHARP);
        } else if (distanceCalc(210, 240)) {
          playTune(instrumentCode, LA_SHARP);
        } else if (distanceCalc(240, 270)) {
          playTune(instrumentCode, TI);
        } else if (distanceCalc(270, 300)) {
          playTune(instrumentCode, HIGH_DO_SHARP);
        } else if (distanceCalc(300, 330)) {
          playTune(instrumentCode, HIGH_RE_SHARP);
        } else if (distanceCalc(330, 360)) {
          playTune(instrumentCode, HIGH_MI);
        } else if (distanceCalc(360, 390)) {
          playTune(instrumentCode, HIGH_FA_SHARP);
        } else if (distanceCalc(390, 420)) {
          playTune(instrumentCode, HIGH_SOL_SHARP);
        } else if (distanceCalc(420, 450)) {
          playTune(instrumentCode, HIGH_LA_SHARP);
        }
      }
    }
  }




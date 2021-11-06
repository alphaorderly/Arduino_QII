#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>
#include <MsTimer2.h>


SoftwareSerial mp3Serial(10, 11);
DFPlayerMini_Fast myDFPlayer;


/***** 디파인 *****/
#define ECHO        6
#define TRIG        5
#define PLAYBUTTON  12

enum instrument {  // 악기 변경용
  OBOE = 1
};

enum pitch {       // 음정 변경용
  DO, DO_SHARP, RE, RE_SHARP, MI, FA, FA_SHARP, SOL, SOL_SHARP, LA, LA_SHARP, TI, 
  HIGH_DO, HIGH_DO_SHARP, HIGH_RE, HIGH_RE_SHARP, HIGH_MI, HIGH_FA, HIGH_FA_SHARP, HIGH_SOL, HIGH_SOL_SHARP, HIGH_LA, HIGH_LA_SHARP, HIGH_TI
};

/** 거리 재는 함수 **/ 

int distance = 0; // 거리 전역변수.

void measureLength() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  distance = pulseIn(ECHO, HIGH) * 34000 / 10000 / 2;

}

void setup() {
  mp3Serial.begin(9600);
  Serial.begin(115200);

  // 핀모드
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(PLAYBUTTON, INPUT);

  // mp3 초기세팅
  myDFPlayer.begin(mp3Serial, true);

  myDFPlayer.volume(30);                       // 볼륨 20

  MsTimer2::set(50, measureLength);
  MsTimer2::start();
}

int instrumentCode = OBOE; // 기본악기는 오보에로

int i = 1;

int distanceCalc(int low, int high) {
  return (low <= distance && distance < high);
}

void playTune(instrument inst, pitch p) {
  myDFPlayer.loop(inst + p);
  while(digitalRead(PLAYBUTTON));
  myDFPlayer.stop();
}

void loop() { 

    if(digitalRead(PLAYBUTTON)) // 버튼 누르면
    {
      delay(15);
      if(1) { // 샾 플랫 안누름
        if(distanceCalc(0, 600)) {
          playTune(OBOE, DO);
        } else if (distanceCalc(600, 900)) {
          playTune(OBOE, RE);
        } else if (distanceCalc(900, 1200)) {
          playTune(OBOE, MI);
        } else if (distanceCalc(1200, 1500)) {
          playTune(OBOE, FA);
        } else if (distanceCalc(1500, 1800)) {
          playTune(OBOE, SOL);
        } else if (distanceCalc(1800, 2100)) {
          playTune(OBOE, LA);
        } else if (distanceCalc(2100, 2400)) {
          playTune(OBOE, TI);
        }
      }
    }

}



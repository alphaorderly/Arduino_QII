#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <MsTimer2.h>

SoftwareSerial mp3Serial(10, 11);
DFRobotDFPlayerMini myDFPlayer;


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

  Serial.println(distance);
}

void setup() {
  mp3Serial.begin(9600);
  Serial.begin(115200);

  // 핀모드
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(PLAYBUTTON, INPUT);

  // mp3 초기세팅
  if (!myDFPlayer.begin(mp3Serial)) {  // mp3 소프트웨어 시리얼 테스트
    Serial.println(F("Mp3 Module Error"));
    while(true);
  }
  Serial.println("MP3 INIT DONE");

  myDFPlayer.volume(30);                       // 볼륨 20
  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);          // 클래식 이퀄라이저
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  MsTimer2::set(100, measureLength);
  MsTimer2::start();
}

int instrumentCode = OBOE; // 기본악기는 오보에로

int i = 1;

void printDistance() {
   if(i++ % 100 == 0) {
    Serial.println(distance);
    Serial.println("---");
    i = 1;
  }
}

int distanceCalc(int low, int high) {
  return (low <= distance && distance < high);
}

void loop() { 

    printDistance();

    if(digitalRead(PLAYBUTTON)) // 버튼 누르면
    {
      if(1) { // 샾 플랫 안누름
        if(distanceCalc(0, 600)) {      
          myDFPlayer.loop(instrumentCode + DO);
          while(digitalRead(PLAYBUTTON) && distanceCalc(0, 600));
          myDFPlayer.stop();
        } else if (distanceCalc(600, 900)) {
          myDFPlayer.loop(instrumentCode + RE);
          while(digitalRead(PLAYBUTTON) && distanceCalc(600, 900));
          myDFPlayer.stop();
        } else if (distanceCalc(900, 1200)) {
          myDFPlayer.loop(instrumentCode + MI);
          while(digitalRead(PLAYBUTTON) && distanceCalc(900, 1200));
          myDFPlayer.stop();
        } else if (distanceCalc(1200, 1500)) {
          myDFPlayer.loop(instrumentCode + FA);
          while(digitalRead(PLAYBUTTON) && distanceCalc(1200, 1500));
          myDFPlayer.stop();
        } else if (distanceCalc(1500, 1800)) {
          myDFPlayer.loop(instrumentCode + SOL);
          while(digitalRead(PLAYBUTTON) && distanceCalc(1500, 1800));
          myDFPlayer.stop();
        } else if (distanceCalc(1800, 2100)) {
          myDFPlayer.loop(instrumentCode + LA);
          while(digitalRead(PLAYBUTTON) && distanceCalc(1800, 2100));
          myDFPlayer.stop();
        } else if (distanceCalc(2100, 2400)) {
          myDFPlayer.loop(instrumentCode + TI);
          while(digitalRead(PLAYBUTTON) && distanceCalc(2100, 2400));
          myDFPlayer.stop();
        }
      }
    }

}



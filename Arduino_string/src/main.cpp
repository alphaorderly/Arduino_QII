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

enum instrument {  // 악기 변경용
  OBOE = 1,
  FLUTE = 25,
  TRUMPET = 49
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

    if(digitalRead(PLAYBUTTON)) // 버튼 누르면
    {
      distance = TOF.readRange();
      Serial.println(distance);
      if(1) { // 샾 플랫 안누름
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
        }
      }
    }

}



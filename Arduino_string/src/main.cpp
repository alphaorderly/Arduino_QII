#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>
#include <Adafruit_VL53L0X.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

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

#define CHECKDURATION 25

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
  pinMode(PLAYBUTTON, INPUT_PULLUP);
  pinMode(SHARP, INPUT_PULLUP);
  pinMode(FLAT, INPUT_PULLUP);
  pinMode(INST_ONE, INPUT_PULLUP);
  pinMode(INST_TWO, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.backlight();

  // mp3 초기세팅
  myDFPlayer.begin(mp3Serial, true);
  myDFPlayer.volume(30);                       // 볼륨 20
}

instrument instrumentCode = OBOE; // 기본악기는 오보에로


int distanceCalc(int low, int high) {
  return (low <= distance && distance < high);
}

void playTune(instrument inst, pitch p, int low, int high) {
  myDFPlayer.loop(inst + p);
  Serial.println(inst + p);
  while(!digitalRead(PLAYBUTTON) && digitalRead(SHARP) && digitalRead(FLAT)) {
    distance = TOF.readRange();
    if(!distanceCalc(low, high)) break;
    delay(CHECKDURATION);
  }
  myDFPlayer.stop();
}

void playSharpTune(instrument inst, pitch p, int low, int high) {
  myDFPlayer.loop(inst + p);
  while(!digitalRead(PLAYBUTTON) && !digitalRead(SHARP) && digitalRead(FLAT)) {
    distance = TOF.readRange();
    if(!distanceCalc(low, high)) break;
    delay(CHECKDURATION);
  }
  myDFPlayer.stop();
}

void playFlatTune(instrument inst, pitch p, int low, int high) {
  myDFPlayer.loop(inst + p);
  while(!digitalRead(PLAYBUTTON) && digitalRead(SHARP) && !digitalRead(FLAT)){
    distance = TOF.readRange();
    if(!distanceCalc(low, high)) break;
    delay(CHECKDURATION);
  }
  myDFPlayer.stop();
}

void loop() { 

  int inst = !digitalRead(INST_ONE) * 2 + !digitalRead(INST_TWO);
  switch(inst) {
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

    if(!digitalRead(PLAYBUTTON)) // 버튼 누르면
    {
      distance = TOF.readRange();
      lcd.setCursor(0, 0);
      switch(instrumentCode) {
        case OBOE:
          lcd.print("OBOE");
          break;
        case FLUTE:
          lcd.print("FLUTE");
          break;
        case TRUMPET:
          lcd.print("TRUMPET");
          break;
        case VIOLIN:
          lcd.print("VIOLIN");
          break;
      }

      lcd.setCursor(0, 1);

      if(digitalRead(SHARP) && digitalRead(FLAT)) { // 샾 플랫 안누름
        if(distanceCalc(0, 40)) {
          lcd.print("DO");
          playTune(instrumentCode, DO, 0, 40);
        } else if (distanceCalc(40, 60)) {
          lcd.print("RE");
          playTune(instrumentCode, RE, 40, 60);
        } else if (distanceCalc(60, 80)) {
          lcd.print("MI");
          playTune(instrumentCode, MI, 60, 80);
        } else if (distanceCalc(80, 100)) {
          lcd.print("FA");
          playTune(instrumentCode, FA, 80, 100);
        } else if (distanceCalc(100, 120)) {
          lcd.print("SOL");
          playTune(instrumentCode, SOL, 100, 120);
        } else if (distanceCalc(120, 140)) {
          lcd.print("LA");
          playTune(instrumentCode, LA, 120, 140);
        } else if (distanceCalc(140, 160)) {
          lcd.print("TI");
          playTune(instrumentCode, TI, 140, 160);
        } else if (distanceCalc(160, 180)) {
          lcd.print("HIGH DO");
          playTune(instrumentCode, HIGH_DO, 160, 180);
        } else if (distanceCalc(180, 200)) {
          lcd.print("HIGH RE");
          playTune(instrumentCode, HIGH_RE, 180, 200);
        } else if (distanceCalc(200, 220)) {
          lcd.print("HIGH MI");
          playTune(instrumentCode, HIGH_MI, 200, 220);
        } else if (distanceCalc(220, 240)) {
          lcd.print("HIGH FA");
          playTune(instrumentCode, HIGH_FA, 220, 240);
        } else if (distanceCalc(240, 260)) {
          lcd.print("HIGH SOL");
          playTune(instrumentCode, HIGH_SOL, 240, 260);
        } else if (distanceCalc(260, 280)) {
          lcd.print("HIGH LA");
          playTune(instrumentCode, HIGH_LA, 260, 280);
        } else if (distanceCalc(280, 300)) {
          lcd.print("HIGH TI");
          playTune(instrumentCode, HIGH_TI, 280, 300);
        }
      } else if (!digitalRead(SHARP) && digitalRead(FLAT)) { // 샾버튼
          if(distanceCalc(0, 40)) {
          lcd.print("DO SHARP");
          playSharpTune(instrumentCode, DO_SHARP, 0, 40);
        } else if (distanceCalc(40, 60)) {
          lcd.print("RE SHARP");
          playSharpTune(instrumentCode, RE_SHARP, 40, 60);
        } else if (distanceCalc(60, 80)) {
          lcd.print("FA");
          playSharpTune(instrumentCode, FA, 60, 80);
        } else if (distanceCalc(80, 100)) {
          lcd.print("FA SHARP");
          playSharpTune(instrumentCode, FA_SHARP, 80, 100);
        } else if (distanceCalc(100, 120)) {
          lcd.print("SOL SHARP");
          playSharpTune(instrumentCode, SOL_SHARP, 100, 120);
        } else if (distanceCalc(120, 140)) {
          lcd.print("LA SHARP");
          playSharpTune(instrumentCode, LA_SHARP, 120, 140);
        } else if (distanceCalc(140, 160)) {
          lcd.print("HIGH DO");
          playSharpTune(instrumentCode, HIGH_DO, 140, 160);
        } else if (distanceCalc(160, 180)) {
          lcd.print("HIGH DO SHARP");
          playSharpTune(instrumentCode, HIGH_DO_SHARP, 160, 180);
        } else if (distanceCalc(180, 200)) {
          lcd.print("HIGH RE SHARP");
          playSharpTune(instrumentCode, HIGH_RE_SHARP, 180, 200);
        } else if (distanceCalc(200, 220)) {
          lcd.print("HIGH FA");
          playSharpTune(instrumentCode, HIGH_FA, 200, 220);
        } else if (distanceCalc(220, 240)) {
          lcd.print("HIGH FA SHARP");
          playSharpTune(instrumentCode, HIGH_FA_SHARP, 220, 240);
        } else if (distanceCalc(240, 260)) {
          lcd.print("HIGH SOL SHARP");
          playSharpTune(instrumentCode, HIGH_SOL_SHARP, 240, 260);
        } else if (distanceCalc(260, 280)) {
          lcd.print("HIGH LA SHARP");
          playSharpTune(instrumentCode, HIGH_LA_SHARP, 260, 280);
        } else if (distanceCalc(280, 300)) {
          lcd.print("HIGH TI");
          playSharpTune(instrumentCode, HIGH_TI, 280, 300);
        }
      } else if (digitalRead(SHARP) && !digitalRead(FLAT)) { // 플랫버튼
          if(distanceCalc(0, 40)) {
          lcd.print("DO");
          playFlatTune(instrumentCode, DO, 0, 40);
        } else if (distanceCalc(40, 60)) {
          lcd.print("DO SHARP");
          playFlatTune(instrumentCode, DO_SHARP, 40, 60);
        } else if (distanceCalc(60, 80)) {
          lcd.print("RE SHARP");
          playFlatTune(instrumentCode, RE_SHARP, 60, 80);
        } else if (distanceCalc(80, 100)) {
          lcd.print("MI");
          playFlatTune(instrumentCode, MI, 80, 100);
        } else if (distanceCalc(100, 120)) {
          lcd.print("FA SHARP");
          playFlatTune(instrumentCode, FA_SHARP, 100, 120);
        } else if (distanceCalc(120, 140)) {
          lcd.print("SOL SHARP");
          playFlatTune(instrumentCode, SOL_SHARP, 120, 140);
        } else if (distanceCalc(140, 160)) {
          lcd.print("LA SHARP");
          playFlatTune(instrumentCode, LA_SHARP, 140, 160);
        } else if (distanceCalc(160, 180)) {
          lcd.print("TI");
          playFlatTune(instrumentCode, TI, 160, 180);
        } else if (distanceCalc(180, 200)) {
          lcd.print("HIGH DO SHARP");
          playFlatTune(instrumentCode, HIGH_DO_SHARP, 180, 200);
        } else if (distanceCalc(200, 220)) {
          lcd.print("HIGH RE SHARP");
          playFlatTune(instrumentCode, HIGH_RE_SHARP, 200, 220);
        } else if (distanceCalc(220, 240)) {
          lcd.print("HIGH MI");
          playFlatTune(instrumentCode, HIGH_MI, 220, 240);
        } else if (distanceCalc(240, 260)) {
          lcd.print("HIGH FA SHARP");
          playFlatTune(instrumentCode, HIGH_FA_SHARP, 240, 260);
        } else if (distanceCalc(260, 280)) {
          lcd.print("HIGH SOL SHARP");
          playFlatTune(instrumentCode, HIGH_SOL_SHARP, 260, 280);
        } else if (distanceCalc(280, 300)) {
          lcd.print("HIGH LA SHARP");
          playFlatTune(instrumentCode, HIGH_LA_SHARP, 280, 300);
        }
      }
      lcd.clear();
    }
    lcd.clear();
  }




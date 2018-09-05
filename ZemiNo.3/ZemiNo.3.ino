#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 accelgyro;

#define LIGHT 10
#define PIN 2
#define DELAY 100
#define LEDS 10
#define LENGTH 20

int val[LEDS][LENGTH][3] = {
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};

//MPUの設定・ステータス
int16_t ax, ay, az;
int16_t gx, gy, gz;

char rgbpin[3] = {A0, A1, A2};//RGBピン

void setup() {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  Serial.begin(9600);
  while (!Serial);

  //センサーの初期化
  Serial.println(("I2Cデバイスの初期化中..."));
  accelgyro.initialize();

  //接続の検証
  Serial.println(("接続の確認中..."));
  Serial.println(accelgyro.testConnection() ? F("センサーの接続に成功") : F("センサーの接続に失敗"));

  for (int i = 0; i < LIGHT; i++) {
    pinMode(PIN + i, OUTPUT);
  }
}

float prevdata = 0.0;
float nowdata = 0.0;
float less = 0.0;
bool plus = true;
float Maxdata, mindata;
float prevtimes = 0.0;
float nowtimes = 0.0;
float effecttimes;
int offtimes = 0;
float activetimes = 0.0;
float averagetimes = 0.0;
int ontimes = 0;

void loop() {
  //加速度センサーの処理
  getgyro();

  //降った場合にのみLEDを点灯する条件
  if (activetimes > 0.0 && activetimes < 500.0) {
    
    delayMicroseconds(activetimes * activetimes / 10);
    for (int i = 0; i < LENGTH; i++) {
      for (int j = 0; j < LEDS; j++) {
        int ledswitch = 0;
        for (int k = 0; k < 3; k++) {
          ledswitch = ledswitch + val[j][i][k];
          analogWrite(rgbpin[k], val[j][i][k]);
        }
        if (ledswitch != 0) {
          digitalWrite(PIN + j, LOW);
        }
        //振る速度でdelay値を変化させる
        delayMicroseconds(activetimes * (activetimes / 50) / (LEDS * LENGTH));
        digitalWrite(PIN + j, HIGH);
      }
    }
    delayMicroseconds(activetimes * activetimes / 10);
  }
}
//加速度センサーの処理----------------------------------------------------
void getgyro() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  prevtimes = nowtimes;
  prevdata = nowdata;
  nowdata = gx;
  less = nowdata - prevdata;//前回と比べて値の変化量

  //上限の判定時の処理
  if (less <= 0 && plus == true && nowdata > 0) {
    Maxdata = nowdata;
    nowtimes = millis();
    plus = false;
  }

  //下限の判定時の処理
  if (less >= 0 && plus == false && nowdata < 0) {
    mindata = nowdata;
    nowtimes = millis();
    plus = true;
  }

  //上限から下限までかかる時間
  effecttimes = nowtimes - prevtimes;

  ontimes += 1;
  if (effecttimes > 0 && effecttimes < 1000) {
    averagetimes = effecttimes;
    offtimes = 0;
  } else {
    offtimes += 1;
    averagetimes = activetimes;
    if (offtimes > 20) {
      averagetimes = 0;
      activetimes = 0;
      ontimes = 0;
    }
  }

  //実際に振る速度
  activetimes = averagetimes;

  Serial.print(millis()); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(Maxdata); Serial.print("\t");
  Serial.print(mindata); Serial.print("\t");
  Serial.print(plus); Serial.print("\t");
  Serial.print(effecttimes); Serial.print("\t");
  Serial.print(ontimes); Serial.print("\t");
  Serial.print(offtimes); Serial.print("\t");
  Serial.print(activetimes); Serial.println("\t");
}


#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 accelgyro;

//MPUの設定・ステータス
int16_t ax, ay, az;
int16_t gx, gy, gz;

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
}

float prevdata = 0.0;
float nowdata = 0.0;
float less = 0.0;
bool plus = true;
float Maxdata, mindata;
float prevtimes = 0.0;
float nowtimes = 0.0;
float effecttimes;

void loop() {
  prevtimes = nowtimes;
  //デバイスから生のデータを取得
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  prevdata = nowdata;
  nowdata = gx;
  less = nowdata - prevdata;
  if (less <= 0 && plus == true && nowdata > 0) {
    Maxdata = nowdata;
    nowtimes = millis();
    plus = false;
  }
  if (less >= 0 && plus == false && nowdata < 0) {
    mindata = nowdata;
    nowtimes = millis();
    plus = true;
  }

  effecttimes = nowtimes - prevtimes;

  Serial.print("a/g:\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(Maxdata); Serial.print("\t");
  Serial.print(mindata); Serial.print("\t");
  Serial.print(plus); Serial.print("\t");
  Serial.print(effecttimes); Serial.println("\t");
//  delay(10);
}

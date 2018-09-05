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

char rgbpin[3] = {A0, A1, A2};//RGBピン

void setup() {
  for (int i = 0; i < LIGHT; i++) {
    pinMode(PIN + i, OUTPUT);
  }
}

void loop() {
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
      delayMicroseconds(DELAY);
      digitalWrite(PIN + j, HIGH);
    }
  }
}


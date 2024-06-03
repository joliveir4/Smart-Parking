#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal display(0);

const int distancia_carro = 10;
const int distancia_maxima = 200;
const int BUZZER = 9;
const int FREQUENCIA_BASE = 2000; 
const int TRIG = 4; 
const int ECHO = 2;
const int ledGreen = 7;
const int ledRed = 8;
float seno;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  display.begin(16, 2);
  display.setBacklight(1);
}

void loop() {
  int distancia = sensor_morcego(TRIG, ECHO);

  if (distancia > distancia_maxima) {
    display.clear();
    display.print("vaga livre");
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    noTone(BUZZER);
  } else if (distancia <= distancia_carro) {
    display.clear();
    display.print("CUIDADO COLISAO");
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    tone(BUZZER, FREQUENCIA_BASE);
  } else {
    display.clear();
    display.print("vaga ocupada");
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    noTone(BUZZER);
  }

  delay(2000);
}

int sensor_morcego(int pinotrig, int pinoecho) {
  digitalWrite(pinotrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinotrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinotrig, LOW);

  return pulseIn(pinoecho, HIGH) / 58;
}

void tocaBuzzer() {
  for (int x = 0; x < 180; x++) {
    seno = (sin(x * 3.1416 / 180));
    int FREQUENCIA = FREQUENCIA_BASE + int(seno * 1000);
    tone(BUZZER, FREQUENCIA);
    delay(2);
  }
}

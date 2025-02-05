#include "Ultrassonico.h"
#include <Arduino.h>

// Definição dos pinos de controle do motor
#define M1 9
#define M2 11
#define dir1 8
#define dir2 10

// Definição dos pinos do ultrassônico
#define TRIG_PIN 4
#define ECHO_PIN 5

int velocidade = 60;

void setupUltrassonico() {
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loopUltrassonico() {
  float distancia = medirDistancia();

  if (distancia < 10.0) {
    pararMotores();
    delay(500);
  } /*else {
    moverParaFrente();
  } */
} 

float medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  if (duracao == 0) return 999;
  return (duracao * 0.034) / 2;
}

void pararMotores() {
  analogWrite(M1, 0);
  analogWrite(M2, 0);
}

void moverParaFrente() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
  analogWrite(M1, velocidade);
  analogWrite(M2, velocidade);
}

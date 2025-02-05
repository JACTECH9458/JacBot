#include "SeguidorDeLinha.h"
#include <Arduino.h>

// Definição dos pinos de controle do motor
#define M1 9  // Pino_Velocidade 1º Motor (0 a 255) - Porta IN2 ponte H
#define M2 11 // Pino_Velocidade 2º Motor (0 a 255) - Porta IN4 ponte H
#define dir1 8  // Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW) - porta IN1 ponte H
#define dir2 10 // Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW) - porta IN3 ponte H

// Definição dos pinos dos sensores
#define pin_S1 7
#define pin_S2 6
bool Sensor1 = 0;
bool Sensor2 = 0;


// Função de inicialização do Seguidor de Linha
void setupSeguidorDeLinha() {
  // Configuração do monitor serial
  Serial.begin(9600); // Inicializa a comunicação serial com a taxa de 9600 bps

  // Setamos os pinos de controle dos motores como saída
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);

  // Setamos a direção inicial do motor como 0, isso fará com que ambos os motores girem para frente
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);

  // Setamos os pinos dos sensores como entrada
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);
}

// Função de execução principal do Seguidor de Linha
void loopSeguidorDeLinha() {

  // Variável responsável por controlar a velocidade dos motores
int velocidade = 75;
int velocidadeMinima = 70;

  delay(20);

  // Neste processo armazenamos o valor lido pelo sensor na variável que armazena tais dados.
  Sensor1 = digitalRead(pin_S1);
  Sensor2 = digitalRead(pin_S2);

  // Exibe os valores dos sensores no monitor serial
  Serial.print("Sensor1: ");
  Serial.print(Sensor1);
  Serial.print(" | Sensor2: ");
  Serial.println(Sensor2);

  // Aqui está toda a lógica de comportamento do robô: Para a cor branca atribuímos o valor 0 e, para a cor preta, o valor 1.
  if ((Sensor1 == 1) && (Sensor2 == 0)) { 
    digitalWrite(dir1, HIGH);          // Inverte o sentido do Motor 1
    analogWrite(M1, velocidadeMinima); // Reduz a velocidade do Motor 1 (gira para trás)
    digitalWrite(dir2, LOW);          // Mantém o Motor 2 para frente
    analogWrite(M2, velocidade);      // Velocidade normal do Motor 2
  }

  if ((Sensor1 == 0) && (Sensor2 == 1)) { 
    digitalWrite(dir1, LOW);          // Mantém o Motor 1 para frente
    analogWrite(M1, velocidade);      // Velocidade normal do Motor 1
    digitalWrite(dir2, HIGH);         // Inverte o sentido do Motor 2
    analogWrite(M2, velocidadeMinima); // Reduz a velocidade do Motor 2 (gira para trás)
  }

  if ((Sensor1 == 0) && (Sensor2 == 0)) { 
    digitalWrite(dir1, LOW);          // Ambos motores para frente
    analogWrite(M1, velocidade);
    digitalWrite(dir2, LOW); 
    analogWrite(M2, velocidade);
  }

  if ((Sensor1 == 1) && (Sensor2 == 1)) {
    digitalWrite(dir1, LOW);
    analogWrite(M1, velocidadeMinima);
    digitalWrite(dir2, LOW);
    analogWrite(M2, velocidadeMinima);
    //delay(200);
  } /*else {
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    analogWrite(M1, velocidade);
    analogWrite(M2, velocidade);
  }*/
}


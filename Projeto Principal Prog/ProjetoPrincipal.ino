#include "SeguidorDeLinha.h"
#include "Ultrassonico.h"

void setup() {
  setupSeguidorDeLinha();
  setupUltrassonico();
}

void loop() {
  loopSeguidorDeLinha();
  loopUltrassonico();
}
 

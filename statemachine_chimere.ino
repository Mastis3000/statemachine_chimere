#include "States.h"

StateMachine sm;

#define fsrpin A0
int fsrreading;

void setup() {
  Serial.begin(115200);

  Serial.println("\n\Chimère");

  sm.changeState(new StateIdle());

}

void loop() {

  sm.loop();

}
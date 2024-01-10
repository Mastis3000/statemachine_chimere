#include "HardwareSerial.h"
#include "Arduino.h"
// This file declares and implements the State* classes, which are the child of State class
// and contains the logic of each state of our application.



#include "StateMachine.h"

class StateIdle : public State {

  void enter() {
    //Serial.println(">>>>>>>>>>>>> StateIdle.enter()");
    Serial.println("appuyez pour dessiner");
  }

  // Loop is declared here, but implemented below, after the declaration of other states
  State* loop();

  void exit() {
    //Serial.println("<<<<<<<<<<<<< StateIdle.exit()");
  }
};


class StateDrawing : public State {

  unsigned long msLastTouch = 0;
  unsigned long msLastMessage = 0;

  void enter();

  // Loop is declared here, but implemented below, after the declaration of other states
  State* loop();

  void exit() {
    //Serial.println("<<<<<<<<<<<<< StateDrawing.exit()");
  }

  void displayMessage();
};


bool isTouch() {
  int val = analogRead(A0);
  //Serial.println(val);
  return val > 5;
}

State* StateIdle::loop() {
  if (isTouch()) {
    return new StateDrawing();
  }
  return NULL;
}

//############################################## STATE DRAWING


void StateDrawing::enter() {
  Serial.println(">>>>>>>>>>>>> StateDrawing.enter()");
  msLastTouch = millis();
  displayMessage();
}

State* StateDrawing::loop() {

  if (isTouch()) {
    msLastTouch = millis();
  }

  // Return to Idle when more than 5000ms elapsed since last tuch
  if (millis() - msLastTouch > 5000) {
    return new StateIdle();
  }

  // display a new message every 10 sec.
  if (millis() - msLastMessage > 10000) {
    displayMessage();
  }

  return NULL;
}

void StateDrawing::displayMessage() {

  char* words[24] = { "chaussure", "arbre", "pomme", "serpent", "route", "bougie", "volcan", "oiseau", "gateau", "pyramide", "cadeau", "crayon", "île", "fleuve", "maison", "orage", "fusée", "bateau", "règle", "livre", "soleil", "allumette", "couteau", "fourchette" };
  long words1;
  words1 = random(sizeof(words) / sizeof(char*));

  char* prompts[3] = { "yeux fermes", "mauvaise main", "un trait" };
  long prompts1;
  prompts1 = random(sizeof(prompts) / sizeof(char*));


  /*char* prompts[3] = { "yeux fermés", "mauvaise main", "un trait" };
  long prompts1;*/

  msLastMessage = millis();
  Serial.println(words[words1]);
  Serial.println(prompts[prompts1]);
}

#include "../include/scenarios.h"
#include "../include/characters.h"

QString Scenario::greetAmos() {
  QMap<int, QString> greetingMsg = {
      {0, "Hey there, been a moment since I've seen a new face in these parts. "
          "My name's Amos, where do you come from? (I could: tell Amos about "
          "Arkansas, tell Amos about Iowa, tell Amos about Kansas)\n\nHint: I "
          "can use the command GOODBYE to end a conversation."},
      {1, ""}};
  if (greetingMsg.contains(
          ensembleObj.getCharacters()[0].getTimesEncountered())) {
    return greetingMsg.value(
        ensembleObj.getCharacters()[0].getTimesEncountered());
  }
  return "";
}

QString Scenario::greetIra() {
  QMap<int, QString> greetingMsg = {{0, "PLACEHOLDER MSG"}, {1, ""}};
  if (greetingMsg.contains(
          ensembleObj.getCharacters()[0].getTimesEncountered())) {
    return greetingMsg.value(
        ensembleObj.getCharacters()[0].getTimesEncountered());
  }
  return "";
}

Scenario scenarioObj;

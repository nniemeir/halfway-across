#include "../../include/entities/dialogue.h"
#include "../../include/entities/characters.h"

QString Dialogue::getPromptMsg() { return promptMsg; }

QString Dialogue::greetAmos() {
  QMap<int, QString> greetingMsg = {
      {0, "Hey there, been a moment since I've seen a new face in these parts. "
          "My name's Amos, where do you come from? (I could: tell Amos about "
          "Arkansas, tell Amos about Iowa, tell Amos about Kansas)\n\nHint: I "
          "can use the command GOODBYE to end a conversation."},
      {1, ""}};
  int timesEncountered = ensembleObj.getCharacters()[0].getTimesEncountered();
  if (greetingMsg.contains(timesEncountered)) {
    return greetingMsg.value(timesEncountered);
  }
  return "";
}

QString Dialogue::greetIra() {
  QMap<int, QString> greetingMsg = {{0, "PLACEHOLDER MSG"}, {1, ""}};
  int timesEncountered = ensembleObj.getCharacters()[1].getTimesEncountered();
  if (greetingMsg.contains(timesEncountered)) {
    return greetingMsg.value(timesEncountered);
  }
  return "";
}

Dialogue dialogueObj;

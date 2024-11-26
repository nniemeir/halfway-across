#include "../../include/entities/dialogue.h"
#include "../../include/entities/characters.h"

QString Dialogue::getPromptMsg() { return promptMsg; }

QString Dialogue::greetLogic(int ensembleIndex) {
  int timesEncountered =
      ensembleObj.getCharacters()[ensembleIndex].getTimesEncountered();
  QMap<int, QString> greetingMsgs =
      ensembleObj.getCharacters()[ensembleIndex].getGreetingMsgs();
  if (greetingMsgs.contains(timesEncountered)) {
    return greetingMsgs.value(timesEncountered);
  }
  return "";
}

Dialogue dialogueObj;

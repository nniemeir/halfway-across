#ifndef DIALOGUE_H
#define DIALOGUE_H
#include "../../include/entities/locations.h"
#include <QRegularExpression>

class Dialogue {
public:
  Dialogue(){};
  static constexpr int START = 0;
  static constexpr int END = 100;
  const QString ASK_INVALID = "It didn't seem like an appropriate question.";
  const QString ASK_REFUSAL =
      "I'm not sure I know you well enough to get into that.";
  const QString DIALOGUE_OVER = "I don't have anymore time to talk.";
  QString promptMsg;
  QString getPromptMsg();
  QString askAmosE1(QString subject, Location *location);
  QString askAmosE1S1(QString subject, Location *location);
  QString askIraE1(QString subject, Location *location);
  QString greetAmos();
  QString greetIra();
  QString tellAmosE1(QString subject, Location *location);
  QString tellAmosE1S0(QString subject, Location *location);
  QString tellAmosE1S3(QString subject, Location *location);
  QString tellIraE1(QString subject, Location *location);
};

extern Dialogue dialogueObj;

#endif // DIALOGUE_H

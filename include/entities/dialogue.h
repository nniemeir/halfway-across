#ifndef DIALOGUE_H
#define DIALOGUE_H
#include "../../include/entities/locations.h"
#include <QRegularExpression>

class Dialogue {
public:
  Dialogue(){};
  static constexpr int START = 0;
  static constexpr int END = 100;
  QString promptMsg;
  QString getPromptMsg();
  QString askAmosE1(QString subject, Location *location);
  QString askAmosE1S1(QString subject, Location *location);
  QString askIraE1(QString subject, Location *location);
  QString greetAmos();
  QString greetIra();
  QString greetLogic(int ensembleIndex);
  QString tellAmosE1(QString subject, Location *location);
  QString tellAmosE1S0(QString subject, Location *location);
  QString tellAmosE1S3(QString subject, Location *location);
  QString tellIraE1(QString subject, Location *location);
};

extern Dialogue dialogueObj;

#endif // DIALOGUE_H

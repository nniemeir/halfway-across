#ifndef DIALOGUE_H
#define DIALOGUE_H
#include "../../include/entities/locations.h"
#include <QRegularExpression>

// Contains the logic for each dialogue scenario
class Dialogue {
public:
  Dialogue(){};
  static constexpr int START = 0;
  static constexpr int END = 100;
  QString getPromptMsg();
  QString askAmosE1(QString subject, Location *location);
  QString askIraE1(QString subject, Location *location);
  QString greetLogic(int ensembleIndex);
  QString tellAmosE1(QString subject, Location *location);
  QString tellIraE1(QString subject, Location *location);

private:
  QString askAmosE1S1(QString subject, Location *location);
  QString greetAmos();
  QString greetIra();
  QString tellAmosE1S0(QString subject, Location *location);
  QString tellAmosE1S3(QString subject, Location *location);
  QString promptMsg;
};

extern Dialogue dialogueObj;

#endif

#ifndef SCENARIOS_H
#define SCENARIOS_H
#include "locations.h"
#include <QRegularExpression>

class Scenario {
public:
  Scenario(){};
  const int START = 0;
  const int END = 100;
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

extern Scenario scenarioObj;

#endif // SCENARIOS_H

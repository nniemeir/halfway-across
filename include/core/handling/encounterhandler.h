#ifndef HANDLING_H
#define HANDLING_H
#include "ui/mainwindow.h"

// Directs input towards the correct encounter logic for a given scenario
class EncounterHandler {
public:
  EncounterHandler();

  void talkLogic(MainWindow *mainWindow, QString verb, QString target,
                 QString subject, Location *location);

private:
  void initMaps();
  QString getResponseMsg(QString verb, QString target, QString subject,
                         Location *location);
  void playVoiceSfx(MainWindow *mainWindow, QString verb);

  QMap<int, std::function<QString(QString, Location *)>> askAmosEncounters;
  QMap<int, std::function<QString(QString, Location *)>> askIraEncounters;
  QMap<int, std::function<QString(QString, Location *)>> tellAmosEncounters;
  QMap<int, std::function<QString(QString, Location *)>> tellIraEncounters;
};

extern EncounterHandler encounterHandlerObj;

#endif

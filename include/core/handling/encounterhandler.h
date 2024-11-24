#ifndef HANDLING_H
#define HANDLING_H
#include "../../../include/ui/mainwindow.h"

class EncounterHandler {
public:
  EncounterHandler();
  void talkLogic(MainWindow *mainWindow, QString verb, QString target,
                 QString subject, Location *location);

private:
  QMap<int, std::function<QString(QString, Location *)>> askAmosEncounters;
  QMap<int, std::function<QString(QString, Location *)>> askIraEncounters;
  QMap<int, std::function<QString(QString, Location *)>> tellAmosEncounters;
  QMap<int, std::function<QString(QString, Location *)>> tellIraEncounters;
  void initMaps();
  void playVoiceSfx(QString verb);
  QString getResponseMsg(QString verb, QString target, QString subject,
                         Location *location);
};

extern EncounterHandler encounterHandlerObj;

#endif

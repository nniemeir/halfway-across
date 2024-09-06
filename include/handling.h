#ifndef HANDLING_H
#define HANDLING_H
#include "../include/mainwindow.h"

class handling {
public:
  handling();
  int validateVerb(QString input);
  void splitInput(MainWindow *mainWindow, QString input);
  void handleVerb(MainWindow *mainWindow, QString verb, QString target,
                  Location *location);

private:
  std::vector<QString> argVerbs;
  std::vector<QString> noArgVerbs;
  QString removeWords(const QString& text, const QStringList& words);
  // Verb-specific handling
  void begin(MainWindow *mainWindow, Location *location);
  void drink(MainWindow *mainWindow, QString target, Location *location);
  void drinkLake(MainWindow *mainWindow, QString target);
  void drop(MainWindow *mainWindow, QString target, Location *location);
  void look(MainWindow *mainWindow, QString target, Location *location);
  void lookCamp(MainWindow *mainWindow, QString target);
  void lookCampPath(MainWindow *mainWindow, QString target, Location *location);
  void lookCave(MainWindow *mainWindow, QString target);
  void lookCaveEntrance(MainWindow *mainWindow, QString target);
  void lookLake(MainWindow *mainWindow, QString target);
  void lookValley(MainWindow *mainWindow, QString target);
  void move(MainWindow *mainWindow, QString target, Location *location);
  void moveCamp(MainWindow *mainWindow, QString target);
  void moveCampPath(MainWindow *mainWindow, QString target);
  void moveCave(MainWindow *mainWindow, QString target);
  void moveCaveEntrance(MainWindow *mainWindow, QString target);
  void moveLake(MainWindow *mainWindow, QString target);
  void moveValley(MainWindow *mainWindow, QString target);
  void remove(MainWindow *mainWindow, QString target);
  void sit(MainWindow *mainWindow, QString target, Location *location);
  void sitCamp(MainWindow *mainWindow, QString target);
  void sleep(MainWindow *mainWindow, Location *location);
  void stand(MainWindow *mainWindow);
  void take(MainWindow *mainWindow, QString target, Location *location);
  void use(MainWindow *mainWindow, QString target, Location *location);
  void useCamp(MainWindow *mainWindow, QString target);
  void useLake(MainWindow *mainWindow, QString target);
  void wait(MainWindow *mainWindow, Location *location);
  void waitLake(MainWindow *mainWindow);
  void wear(MainWindow *mainWindow, QString target);
};

extern handling handle;

#endif // HANDLING_H

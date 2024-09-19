#ifndef HANDLING_H
#define HANDLING_H
#include "../include/mainwindow.h"
#include <QRegularExpression>

class Handling {
public:
  Handling();
  // Formatting
  QString getArticle(QString target);
  // General handling
  int validateVerb(QString input);
  void splitInput(MainWindow *mainWindow, QString input);
  void handleVerb(MainWindow *mainWindow, QString verb, QString target,
                  Location *location);
  // Journal
  QString getLastCommand() const;
  void setLastCommand(QString command);

private:
  // Input validation
  std::vector<QString> argVerbs;
  std::vector<QString> noArgVerbs;
  QString removeFillerWords(const QString &text, const QStringList &words);
  // Journal
  QString lastCommand;
  // Messages
  void gameOverMsg(MainWindow *mainWindow, QString reason);
  void missingItemMsg(MainWindow *mainWindow, QString target);
  void notAllowedDirMsg(MainWindow *mainWindow, QString verb, QString target);
  void notAllowedInLocMsg(MainWindow *mainWindow, QString action);
  void tiredMsg(MainWindow *mainWindow);
  void waitMsg(MainWindow *mainWindow);
  // Verb-specific handling functions
  void begin(MainWindow *mainWindow, Location *location);
  void cook(MainWindow *mainWindow, QString target, Location *location);
  void craft(MainWindow *mainWindow, QString target);
  void cry(MainWindow *mainWindow);
  void drink(MainWindow *mainWindow, QString target, Location *location);
  void drinkLake(MainWindow *mainWindow, QString target);
  void drop(MainWindow *mainWindow, QString target, Location *location);
  void eat(MainWindow *mainWindow, QString target);
  void examine(MainWindow *mainWindow, QString target);
  void hunt(MainWindow *mainWindow, QString target, Location *location);
  void look(MainWindow *mainWindow, QString target, Location *location);
  void load(MainWindow *mainWindow, QString target);
  void lookCamp(MainWindow *mainWindow, QString target);
  void lookCampPath(MainWindow *mainWindow, QString target);
  void lookCave(MainWindow *mainWindow, QString target);
  void lookCaveEntrance(MainWindow *mainWindow, QString target);
  void lookLake(MainWindow *mainWindow, QString target);
  void lookValley(MainWindow *mainWindow, QString target);
  void move(MainWindow *mainWindow, QString target, Location *location);
  void moveCamp(MainWindow *mainWindow, QString target);
  void moveCampPath(MainWindow *mainWindow, QString target);
  void moveCave(MainWindow *mainWindow, QString target);
  void moveCaveEntrance(MainWindow *mainWindow, QString target);
  void moveCaveLit(MainWindow *mainWindow, QString target);
  void moveLake(MainWindow *mainWindow, QString target);
  void moveValley(MainWindow *mainWindow, QString target);
  void remove(MainWindow *mainWindow, QString target);
  void script(MainWindow *mainWindow);
  void sit(MainWindow *mainWindow, QString target, Location *location);
  void sitCamp(MainWindow *mainWindow, QString target);
  void sleep(MainWindow *mainWindow, Location *location);
  void stand(MainWindow *mainWindow);
  void take(MainWindow *mainWindow, QString target, Location *location);
  void use(MainWindow *mainWindow, QString target, Location *location);
  void useCamp(MainWindow *mainWindow, QString target);
  void useCave(MainWindow *mainWindow, QString target);
  void useLake(MainWindow *mainWindow, QString target);
  void unscript(MainWindow *mainWindow);
  void version(MainWindow *mainWindow);
  void wait(MainWindow *mainWindow, Location *location);
  void waitFishing(MainWindow *mainWindow, int rodIndex);
  void waitLake(MainWindow *mainWindow);
  void wear(MainWindow *mainWindow, QString target);
  void yell(MainWindow *mainWindow);
};

extern Handling handle;

#endif

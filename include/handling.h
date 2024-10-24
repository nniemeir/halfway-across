#ifndef HANDLING_H
#define HANDLING_H
#include "../include/mainwindow.h"
#include <QRegularExpression>

class Handling {
public:
  Handling();
  // Formatting
  QString getArticle(QString target);
  // Script
  QString getLastCommand() const;
  void setLastCommand(QString command);
  // General handling
  void handleVerb(MainWindow *mainWindow, QString verb, QString target,
                  QString subject, Location *location);

  void splitInput(MainWindow *mainWindow, QString input);
  int validateVerb(QString input);
  // Messages
  void confusedMsg(MainWindow *mainWindow);

private:
  // Handling
  void handleVerbActions(MainWindow *mainWindow, QString verb, QString target,
                         QString subject, Location *location,
                         QMap<QString, std::function<void()>> validActions,
                         QMap<QString, std::function<void()>> invalidActions);
  // Filler word removal
  static void initFillerWords(const QStringList &words);
  QString removeFillerWords(const QString &text);
  // Messages
  void characterNotActiveMsg(MainWindow *mainWindow, QString target);
  void gameOverMsg(MainWindow *mainWindow, QString reason);
  void missingItemMsg(MainWindow *mainWindow, QString target);
  void notAllowedDirMsg(MainWindow *mainWindow, QString verb, QString target);
  void notAllowedInLocMsg(MainWindow *mainWindow, QString action);
  void tiredMsg(MainWindow *mainWindow);
  void waitMsg(MainWindow *mainWindow);
  // Verb-specific handling functions
  void ask(MainWindow *mainWindow, QString target, QString subject,
           Location *location);
  void askAmos(MainWindow *mainWindow, QString subject, Location *location);
  void askIra(MainWindow *mainWindow, QString subject, Location *location);
  void begin(MainWindow *mainWindow, Location *location);
  void cook(MainWindow *mainWindow, QString target, Location *location);
  void craft(MainWindow *mainWindow, QString target);
  void cry(MainWindow *mainWindow);
  void diagnose(MainWindow *mainWindow, Location *location);
  void drink(MainWindow *mainWindow, QString target, Location *location);
  void drinkCanteen(MainWindow *mainWindow, QString target);
  void drinkLake(MainWindow *mainWindow, QString target);
  void eat(MainWindow *mainWindow, QString target);
  void examine(MainWindow *mainWindow, QString target);
  void fill(MainWindow *mainWindow, QString target, Location *location);
  void help(MainWindow *mainWindow);
  void hunt(MainWindow *mainWindow, QString target, Location *location);
  void look(MainWindow *mainWindow, QString target, Location *location);
  void load(MainWindow *mainWindow, QString target);
  void lookCamp(MainWindow *mainWindow, QString target);
  void lookForestPath(MainWindow *mainWindow, QString target);
  void lookCave(MainWindow *mainWindow, QString target);
  void lookCaveEntrance(MainWindow *mainWindow, QString target);
  void lookLake(MainWindow *mainWindow, QString target);
  void lookValley(MainWindow *mainWindow, QString target);
  void move(MainWindow *mainWindow, QString target, Location *location);
  void moveCamp(MainWindow *mainWindow, QString target);
  void moveForestPath(MainWindow *mainWindow, QString target);
  void moveCave(MainWindow *mainWindow, QString target);
  void moveCaveEntrance(MainWindow *mainWindow, QString target);
  void moveCaveLit(MainWindow *mainWindow, QString target);
  void moveLake(MainWindow *mainWindow, QString target);
  void moveValley(MainWindow *mainWindow, QString target);
  void put(MainWindow *mainWindow, QString target, QString reason,
           Location *location);
  void read(MainWindow *mainWindow, Location *location, QString target);
  void remove(MainWindow *mainWindow, QString target);
  void script(MainWindow *mainWindow);
  void shoot(MainWindow *mainWindow, QString target, Location *location);
  void sit(MainWindow *mainWindow, QString target, Location *location);
  void sitCamp(MainWindow *mainWindow, QString target);
  void skin(MainWindow *mainWindow, QString target, Location *location);
  void sleep(MainWindow *mainWindow, Location *location);
  void stand(MainWindow *mainWindow);
  void take(MainWindow *mainWindow, QString target, Location *location);
  void tell(MainWindow *mainWindow, QString target, QString subject,
            Location *location);
  void tellAmos(MainWindow *mainWindow, QString subject, Location *location);
  void tellIra(MainWindow *mainWindow, QString subject, Location *location);
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
  void yell(MainWindow *mainWindow, Location *location);
  // Input validation
  std::vector<QString> argVerbs;
  std::vector<QString> noArgVerbs;
  // Filler word removal
  QStringList fillerWords;
  static QRegularExpression fillerWordsRegex;
  static const QRegularExpression multiSpaces;
  // Script
  QString lastCommand;
};

extern Handling handlingObj;

#endif

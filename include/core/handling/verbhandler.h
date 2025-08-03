#ifndef VERBHANDLER_H
#define VERBHANDLER_H
#include "ui/mainwindow.h"

// Contains the logic for each supported verb
class VerbHandler {
public:
  VerbHandler();
  static constexpr int ITEM_NOT_FOUND = -1;
  void process(MainWindow *mainWindow, QString verb, QString target,
               QString subject, Location *location);

private:
  void processActions(MainWindow *mainWindow, QString verb, QString target,
                      QString subject, Location *location,
                      QMap<QString, std::function<void()>> validActions,
                      QMap<QString, std::function<void()>> invalidActions1,
                      QMap<QString, std::function<void()>> invalidActions2);
  // Verb Functions
  void ask(MainWindow *mainWindow, QString target, QString subject,
           Location *location);
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
  void goodbye(MainWindow *mainWindow, Location *location);
  void greet(MainWindow *mainWindow);
  void help(MainWindow *mainWindow);
  void hunt(MainWindow *mainWindow, QString target, Location *location);
  void look(MainWindow *mainWindow, QString target, Location *location);
  bool lookingAtCharacter(MainWindow *mainWindow, QString target,
                          Location *location);
  void load(MainWindow *mainWindow, QString target);
  void move(MainWindow *mainWindow, QString target, Location *location);
  bool moveCamp(MainWindow *mainWindow, QString target);
  bool moveForestPath(MainWindow *mainWindow, QString target);
  bool moveCave(MainWindow *mainWindow, QString target);
  bool moveCaveEntrance(MainWindow *mainWindow, QString target);
  bool moveCaveLit(MainWindow *mainWindow, QString target);
  bool moveLake(MainWindow *mainWindow, QString target);
  bool moveValley(MainWindow *mainWindow, QString target);
  void put(MainWindow *mainWindow, QString target, QString reason,
           Location *location);
  void read(MainWindow *mainWindow, Location *location, QString target);
  void remove(MainWindow *mainWindow, QString target);
  void script(MainWindow *mainWindow);
  void shoot(MainWindow *mainWindow, QString target, Location *location);
  void sit(MainWindow *mainWindow, QString target, Location *location);
  void sitOnFireAtCamp(MainWindow *mainWindow);
  void sitOnLogAtCamp(MainWindow *mainWindow);
  void skin(MainWindow *mainWindow, QString target, Location *location);
  void sleep(MainWindow *mainWindow, Location *location);
  void stand(MainWindow *mainWindow);
  void take(MainWindow *mainWindow, QString target, Location *location);
  void talk(MainWindow *mainWindow, QString verb, QString target,
            QString subject, Location *location);
  void use(MainWindow *mainWindow, QString target, Location *location);
  void useLanternAtCave(MainWindow *mainWindow);
  void useChiselAtLake(MainWindow *mainWindow);
  void useRodAtLake(MainWindow *mainWindow);
  void unscript(MainWindow *mainWindow);
  void version(MainWindow *mainWindow);
  void wait(MainWindow *mainWindow, Location *location);
  void waitFishing(MainWindow *mainWindow, int rodIndex);
  void waitLake(MainWindow *mainWindow);
  void wear(MainWindow *mainWindow, QString target);
  void yell(MainWindow *mainWindow, Location *location);
};

extern VerbHandler verbHandlerObj;

#endif

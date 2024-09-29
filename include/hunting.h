#ifndef HUNTING_H
#define HUNTING_H
#include "../include/mainwindow.h"

class Hunting
{
public:
  Hunting();
  void hunt(MainWindow *mainWindow, QString target,
            Location *location);
  bool recoveredArrow(bool hitTarget);
  void skinAnimal(MainWindow *mainWindow, QString target);
  bool assessDamage(QString target);
  QString getActiveAnimal() const;
  void setActiveAnimal(QString animal);
  bool hitTarget(QString target);
  std::vector<Item> &getSlainAnimals();

private:
  bool foundAnimal(QString target);
  void huntScenario(MainWindow *mainWindow, QString target, int arrowIndex);
  std::vector<QString> validAnimals;
  std::vector<Item> slainAnimals;
  QString activeAnimal;
  std::vector<Item> bearParts;
  std::vector<Item> deerParts;
  std::vector<Item> foxParts;
  std::vector<Item> rabbitParts;
};

extern Hunting hunting;

#endif // HUNTING_H

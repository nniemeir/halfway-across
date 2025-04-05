#ifndef HUNTING_H
#define HUNTING_H
#include "../../include/entities/locations.h"
#include "../../include/items/item.h"
#include "../../include/ui/mainwindow.h"
#include <QMap>

// Handles the logic for the hunting activity
class Hunting {
public:
  Hunting();
  static constexpr int ANIMAL_INVALID = -1;
  static constexpr int ANIMAL_FOUND = 0;
  static constexpr int ANIMAL_NOT_FOUND = 1;
  QString getActiveAnimal() const;
  int getDailyAttempts() const;
  std::vector<Item> &getSlainAnimals();
  void setActiveAnimal(QString animal);
  void resetDailyAttempts();
  int seek(QString target, int arrowIndex);
  QString processSeekResult(MainWindow *mainWindow, QString target, int arrowIndex);
  bool hitTarget(QString target);
  bool assessDamage(QString target);
  bool recoveredArrow(bool hitTarget);
  bool skinCarcass(QString target, Location *location);

private:
  bool foundAnimal(QString target);
  QString activeAnimal;
  int dailyAttempts;
  std::vector<Item> animalCarcasses;
  std::vector<QString> validAnimals;
  std::vector<Item> bearParts;
  std::vector<Item> deerParts;
  std::vector<Item> foxParts;
  std::vector<Item> rabbitParts;
};

extern Hunting huntingObj;

#endif

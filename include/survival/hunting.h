#ifndef HUNTING_H
#define HUNTING_H
#include "../../include/entities/locations.h"
#include "../../include/items/item.h"
#include <QMap>

class Hunting {
public:
  Hunting();
  static constexpr int ANIMAL_INVALID = -1;
  static constexpr int ANIMAL_FOUND = 0;
  static constexpr int ANIMAL_NOT_FOUND = 1;
  QString getActiveAnimal() const;
  int getDailyHunts() const;
  std::vector<Item> &getSlainAnimals();
  void setActiveAnimal(QString animal);
  int activity(QString target, int arrowIndex);
  bool assessDamage(QString target);
  bool hitTarget(QString target);
  bool recoveredArrow(bool hitTarget);
  bool skinAnimal(QString target, Location *location);
  void resetDailyHunts();

private:
  bool foundAnimal(QString target);
  std::vector<Item> slainAnimals;
  std::vector<QString> validAnimals;
  std::vector<Item> bearParts;
  std::vector<Item> deerParts;
  std::vector<Item> foxParts;
  std::vector<Item> rabbitParts;
  QString activeAnimal;
  int dailyHunts;
};

extern Hunting huntingObj;

#endif // HUNTING_H

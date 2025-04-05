#ifndef WORLD_H
#define WORLD_H
#include "../../include/entities/characters.h"
#include "../../include/entities/locations.h"

// Manages the game's environment
class World {
public:
  World();
  static constexpr int DAY_AMOS_E1 = 8;
  static constexpr int DAY_IRA_E1 = 13;
  Character *getActiveCharacter();
  QString getActiveCharacterBrief();
  int getChiseledIce() const;
  bool getConversing() const;
  bool getConversedToday() const;
  Location *getCurrentLocation() const;
  int getCurrentTemperature() const;
  QString getCurrentWeather() const;
  int getDay() const;
  void setActiveCharacter(Character *newCharacter);
  void setChiseledIce(bool newValue);
  void setConversing(bool newValue);
  void setConversedToday(bool newValue);
  void setCurrentLocation(Location *location);
  QString advanceDay();
  bool rollDice(const int probability);
  bool validDirection(const QString &value);

private:
  bool applyColdDmg();
  Character *generateCharacter();
  int generateTemperature();
  QString generateWeather();
  Character *activeCharacter;
  Location *currentLocation;
  int currentTemperature;
  QString currentWeather;
  bool chiseledIce;
  bool conversing;
  bool conversedToday;
  int day;
  std::vector<QString> directions;
};

extern World worldObj;

#endif

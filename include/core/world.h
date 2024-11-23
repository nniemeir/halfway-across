#ifndef WORLD_H
#define WORLD_H
#include "../../include/entities/characters.h"
#include "../../include/entities/locations.h"

class World {
public:
  World();
  static constexpr int DAY_AMOS_E1 = 8;
  static constexpr int DAY_IRA_E1 = 13;
  Character *getActiveCharacter();
  int getChiseledIce() const;
  Location *getCurrentLocation() const;
  int getCurrentTemperature() const;
  QString getCurrentWeather() const;
  int getDay() const;
  bool getGreetedNPC() const;
  bool getSocialized() const;
  void setActiveCharacter(Character *newCharacter);
  void setChiseledIce(bool newValue);
  void setCurrentLocation(Location *location);
  void setGreetedNPC(bool newValue);
  void setSocialized(bool newValue);
  QString getActiveCharacterBrief();
  QString advanceDay();
  bool roll(const int probability);
  bool validDirection(const QString &value);

private:
  Character *activeCharacter;
  Location *currentLocation;
  int day;
  int currentTemperature;
  QString currentWeather;
  bool chiseledIce;
  Character *generateCharacter();
  int generateTemperature();
  QString generateWeather();
  bool generateTempDebuff();
  std::vector<QString> directions;
  bool greetedNPC;
  bool socialized;
};

extern World worldObj;
#endif

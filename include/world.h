#ifndef WORLD_H
#define WORLD_H
#include "../include/characters.h"
#include "../include/item.h"
#include "../include/locations.h"

class World {
public:
  World();
  typedef enum {
    TRAVEL_YES = 1,
    TRAVEL_BLIZZARD,
    TRAVEL_TIRED
  } TravelResponses;
  const int FIRST_IRA_ENCOUNTER = 8;
  const int FIRST_AMOS_ENCOUNTER = 13;
  Character *getActiveCharacter();
  int getChiseledIce() const;
  Location *getCurrentLocation() const;
  int getCurrentTemperature() const;
  QString getCurrentWeather() const;
  int getDay() const;
  void setActiveCharacter(Character *newCharacter);
  void setChiseledIce(int newValue);
  void setCurrentLocation(Location *location);

  QString advanceDay();
  bool roll(const int probability);
  bool validDirection(const QString &value);

private:
  Character *activeCharacter;
  Location *currentLocation;
  int day;
  int currentTemperature;
  QString currentWeather;
  int chiseledIce;
  Character *generateCharacter();
  int generateTemperature();
  QString generateWeather();
  int generateTempDebuff();
  std::vector<QString> directions;
};

extern World worldObj;
#endif

#ifndef WORLD_H
#define WORLD_H
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

  int getChiseledIce() const;
  Location *getCurrentLocation() const;
  int getCurrentTemperature() const;
  QString getCurrentWeather() const;
  int getDay() const;
  void setChiseledIce(int newValue);
  void setCurrentLocation(Location *location);

  QString advanceDay();
  bool roll(const int probability);
  bool validDirection(const QString &value);

private:
  Location *currentLocation;
  int day;
  int currentTemperature;
  QString currentWeather;
  int chiseledIce;
  int generateTemperature();
  QString generateWeather();
  std::vector<QString> directions;
};

extern World worldObj;
#endif

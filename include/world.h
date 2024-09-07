#ifndef WORLD_H
#define WORLD_H
#include "../include/locations.h"
#include "item.h"
#include <time.h>

class worldStats {
public:
  worldStats();
    typedef enum { TRAVEL_YES = 1, TRAVEL_BLIZZARD, TRAVEL_TIRED } TravelResponses;

  // Day
  void advanceDay();
  int getDay() const;

  // Location
  Location *getCurrentLocation() const;
  void initializeLocation(Location *initialLocation);

  void setCurrentLocation(Location *location);

  // Day-specific
  int getCurrentTemperature() const;
  QString getCurrentWeather() const;
  int getChiseledIce() const;
  void setChiseledIce(int newValue);
  int getLineSet() const;
  void setLineSet(int newValue);
  int travelChecks();

  QString generateFish();
  int searchFish(const QString &itemName) const;
  QString getFishName(int index) const;
  int getFishEffect(int index) const;
  int getFishQuantity(int index) const;
  const item &getFish(int index) const;

  bool validDirection(const QString &value);

private:
  int day;
  Location *currentLocation;
  int currentTemperature;
  QString currentWeather;
  int chiseledIce;
  int lineSet;
  int generateTemperature();
  QString generateWeather();
  std::vector<item> fish;
  std::vector<QString> directions;
};


extern worldStats world;
#endif // WORLD_H

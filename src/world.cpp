#include "../include/world.h"
#include "../include/player.h"

World world;

// The temperature and weather for Day 1 are the same each time to avoid
// immediately trapping the player at camp
World::World()
    : currentLocation(nullptr), day(1), currentTemperature(32),
      currentWeather("clear"), chiseledIce(0), conspicuous(true),
      fish{{"CUTTHROAT TROUT", 1, 0, 25, "RAW MEAT", "NONE"},
           {"BROOK TROUT", 1, 0, 25, "RAW MEAT", "NONE"},
           {"RAINBOW TROUT", 1, 0, 30, "RAW MEAT", "NONE"},
           {"BROWN TROUT", 1, 0, 35, "RAW MEAT", "NONE"}},
      directions{"NORTH", "WEST", "SOUTH", "EAST", "N", "W", "S", "E"} {}

bool World::validDirection(const QString &value) {
  return std::find(directions.begin(), directions.end(), value) !=
         directions.end();
}

int World::advanceDay() {
  player.setEnergy(1);
  if (player.setHunger(player.getHunger() - 20)) {
    return 1;
  } else if (player.setThirst(player.getThirst() - 30)) {
    return 1;
  }
  setChiseledIce(0);
  day++;
  currentTemperature = generateTemperature();
  currentWeather = generateWeather();
  return 0;
}

void World::initializeLocation(Location *initialLocation) {
  currentLocation = initialLocation;
}

int World::getDay() const { return day; }

Location *World::getCurrentLocation() const { return currentLocation; }

void World::setCurrentLocation(Location *location) {
  currentLocation = location;
}

int World::getChiseledIce() const { return chiseledIce; }

void World::setChiseledIce(int newValue) { chiseledIce = newValue; }

int World::getLineSet() const { return lineSet; }

void World::setLineSet(int newValue) { lineSet = newValue; }

bool World::getConspicuous() const { return conspicuous; }

void World::setConspicuous(bool newValue) { conspicuous = newValue; }

// A chance existing for the weather to trap the player at camp is intended to
// encourage them to plan ahead
int World::travelChecks() {
  if (currentWeather == "snowing heavily") {
    return TRAVEL_BLIZZARD;
  } else if (player.getEnergy() == 0) {
    return TRAVEL_TIRED;
  } else {
    return TRAVEL_YES;
  }
}

int World::getCurrentTemperature() const { return currentTemperature; }

QString World::getCurrentWeather() const { return currentWeather; }

// A given day's temperature will have an effect on
// how high the warmth stat must be to avoid losing health
int World::generateTemperature() {
  int temperature = rand() % (30 + 1);
  return temperature;
}

// A given day's weather will have an effect on
// what actions the player can take and how likely they are to succeed at them
QString World::generateWeather() {
  float blizzardProb = 5;
  float snowyProb = 20;
  float cloudyProb = 50;
  int prob = rand() % 100;
  if (prob < blizzardProb) {
    return "snowing heavily";
  } else if (prob < snowyProb) {
    return "snowing";
  } else if (prob < cloudyProb) {
    return "cloudy";
  } else {
    return "clear";
  }
}

// The odds will differ by bait type once that is implemented
QString World::generateFish() {
  float brownTroutProb = 10;
  float rainbowTroutProb = 30;
  float brookTroutProb = 60;
  int prob = rand() % 100;
  if (prob < brownTroutProb) {
    return "BROWN TROUT";
  } else if (prob < rainbowTroutProb) {
    return "RAINBOW TROUT";
  } else if (prob < brookTroutProb) {
    return "BROOK TROUT";
  } else {
    return "CUTTHROAT TROUT";
  }
}

std::vector<Item> &World::getFishInventory() { return fish; }

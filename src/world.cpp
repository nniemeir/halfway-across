#include "../include/fishing.h"
#include "../include/hunting.h"
#include "../include/player.h"
#include "../include/world.h"

World worldObj;

// The temperature and weather for Day 1 are the same each time to avoid
// immediately trapping the player at camp
World::World()
    : currentLocation(nullptr), day(1), currentTemperature(32),
      currentWeather("clear"), chiseledIce(0),
      directions{"NORTH", "WEST", "SOUTH", "EAST", "N", "W", "S", "E"} {}

int World::getChiseledIce() const { return chiseledIce; }

Location *World::getCurrentLocation() const { return currentLocation; }

int World::getCurrentTemperature() const { return currentTemperature; }

QString World::getCurrentWeather() const { return currentWeather; }

int World::getDay() const { return day; }

void World::setChiseledIce(int newValue) { chiseledIce = newValue; }

void World::setCurrentLocation(Location *location) {
  currentLocation = location;
}

QString World::advanceDay() {
  playerObj.setEnergy(1);
  int newCryCooldown;
  if (playerObj.getCryCooldown() >= 1) {
    newCryCooldown = playerObj.getCryCooldown() - 1;
  } else {
    newCryCooldown = 0;
  }
  playerObj.setCryCooldown(newCryCooldown);
  if (playerObj.setHunger(playerObj.getHunger() - 20)) {
    return "HUNGER";
  } else if (playerObj.setThirst(playerObj.getThirst() - 30)) {
    return "THIRST";
  }
  setChiseledIce(0);
  huntingObj.resetDailyHunts();
  fishingObj.resetDailyFished();
  day++;
  currentTemperature = generateTemperature();
  currentWeather = generateWeather();
  return "";
}

bool World::roll(const int probability) {
  int num = rand() % 100;
  if (num < probability) {
    return true;
  } else {
    return false;
  }
}

bool World::validDirection(const QString &value) {
  return std::find(directions.begin(), directions.end(), value) !=
         directions.end();
}

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
  if (prob < blizzardProb && currentWeather != "snowing heavily") {
    return "snowing heavily";
  } else if (prob < snowyProb) {
    return "snowing";
  } else if (prob < cloudyProb) {
    return "cloudy";
  } else {
    return "clear";
  }
}

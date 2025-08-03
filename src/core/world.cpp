#include "core/world.h"
#include "entities/player.h"
#include "survival/fishing.h"
#include "survival/hunting.h"

World::World()
    : activeCharacter(nullptr), currentLocation(nullptr), day(1),
      currentTemperature(30), currentWeather("clear"), conversing(false),
      conversedToday(false), chiseledIce(false),
      directions{"NORTH", "WEST", "SOUTH", "EAST", "N", "W", "S", "E"} {}

Character *World::getActiveCharacter() { return activeCharacter; }

QString World::getActiveCharacterBrief() {
  QString activeCharacterBrief;
  if (activeCharacter == nullptr) {
    return activeCharacterBrief;
  }
  if (activeCharacter->getLocation() != currentLocation->getName()) {
    return activeCharacterBrief;
  }
  if (activeCharacter->getTimesEncountered() == 0) {
    activeCharacterBrief.append(activeCharacter->getBriefUnknown());
  } else {
    activeCharacterBrief.append(activeCharacter->getBriefKnown());
  }
  if (day == 8 && !conversedToday) {
    activeCharacterBrief.append(
        "\nHint: I can start a conversation by using the command GREET.");
  }
  return activeCharacterBrief;
}

int World::getChiseledIce() const { return chiseledIce; }

bool World::getConversing() const { return conversing; }

bool World::getConversedToday() const { return conversedToday; }

Location *World::getCurrentLocation() const { return currentLocation; }

int World::getCurrentTemperature() const { return currentTemperature; }

QString World::getCurrentWeather() const { return currentWeather; }

int World::getDay() const { return day; }

void World::setActiveCharacter(Character *newCharacter) {
  activeCharacter = newCharacter;
}

void World::setChiseledIce(bool newValue) { chiseledIce = newValue; }

void World::setConversing(bool newValue) { conversing = newValue; }

void World::setConversedToday(bool newValue) { conversedToday = newValue; }

void World::setCurrentLocation(Location *location) {
  currentLocation = location;
}

QString World::advanceDay() {
  playerObj.setEnergized(true);
  int newCryCooldown;
  if (playerObj.getCryCooldown() >= 1) {
    newCryCooldown = playerObj.getCryCooldown() - 1;
  } else {
    newCryCooldown = 0;
  }
  playerObj.setCryCooldown(newCryCooldown);
  if (!playerObj.setHunger(playerObj.getHunger() - 20)) {
    return "HUNGER";
  }
  if (!playerObj.setThirst(playerObj.getThirst() - 30)) {
    return "THIRST";
  }
  if (!applyColdDmg()) {
    return "WARMTH";
  }
  setChiseledIce(false);
  worldObj.setConversedToday(false);
  huntingObj.resetDailyAttempts();
  fishingObj.resetDailyAttempts();
  day++;
  currentTemperature = generateTemperature();
  currentWeather = generateWeather();
  if (currentWeather != "snowing heavily" && day > 7) {
    Character *potentialActiveCharacter = generateCharacter();
    setActiveCharacter(potentialActiveCharacter);
  }
  return "";
}

bool World::rollDice(const int probability) {
  int num = rand() % 100;
  if (num < probability) {
    return true;
  }
  return false;
}

bool World::validDirection(const QString &value) {
  return std::find(directions.begin(), directions.end(), value) !=
         directions.end();
}

bool World::applyColdDmg() {
  int currentWarmth = playerObj.getWarmth();
  int healthLoss = 0;
  if (currentTemperature < 5) {
    if (currentWarmth < 25) {
      return 1;
    } else if (currentWarmth < 50) {
      healthLoss = 20;
    } else if (currentWarmth < 75) {
      healthLoss = 10;
    } else {
      healthLoss = 5;
    }
  } else if (currentTemperature < 10) {
    if (currentWarmth < 25) {
      healthLoss = 20;
    } else if (currentWarmth < 50) {
      healthLoss = 10;
    } else if (currentWarmth < 75) {
      healthLoss = 5;
    } else {
      healthLoss = 2;
    }
  } else if (currentTemperature < 15) {
    if (currentWarmth < 25) {
      healthLoss = 10;
    } else if (currentWarmth < 50) {
      healthLoss = 5;
    } else if (currentWarmth < 75) {
      healthLoss = 2;
    }
  } else if (currentTemperature < 20) {
    if (currentWarmth < 25) {
      healthLoss = 5;
    } else if (currentWarmth < 50) {
      healthLoss = 2;
    }
  }
  if (healthLoss > 0) {
    return playerObj.setHealth(playerObj.getHealth() - healthLoss);
  }
  return true;
}

Character *World::generateCharacter() {
  if (day == DAY_AMOS_E1) {
    return ensembleObj.getCharacter(0); // Amos
  }
  if (day == DAY_IRA_E1) {
    return ensembleObj.getCharacter(1); // Ira
  }
  int index = 0;
  std::vector<int> matchesIndex = {};
  for (auto const &characterObj : ensembleObj.getCharacters()) {
    if (characterObj.getDaysSinceEncountered() >= characterObj.getFrequency()) {
      matchesIndex.push_back(index);
    }
    index++;
  }
  if (matchesIndex.size() == 1) {
    ensembleObj.getCharacter(matchesIndex[0])->setDaysSinceEncountered(0);
    return ensembleObj.getCharacter(matchesIndex[0]);
  }
  if (matchesIndex.size() > 1) {
    int chosenMatchIndex = rand() % matchesIndex.size();
    ensembleObj.getCharacter(matchesIndex[chosenMatchIndex])
        ->setDaysSinceEncountered(0);
    return ensembleObj.getCharacter(matchesIndex[chosenMatchIndex]);
  }
  return nullptr;
}

// A given day's temperature effects
// how high the warmth stat must be to avoid losing health
int World::generateTemperature() {
  int lowerBound;
  int upperBound;
  int temperature;
  if (day <= 14) {
    lowerBound = 20;
    upperBound = 30;
  } else if (day <= 28) {
    lowerBound = 10;
    upperBound = 20;
  } else if (day <= 35) {
    lowerBound = 0;
    upperBound = 10;
  } else if (day <= 42) {
    lowerBound = 0;
    upperBound = 5;
  } else if (day <= 56) {
    lowerBound = 10;
    upperBound = 20;
  } else {
    lowerBound = 20;
    upperBound = 30;
  }
  return lowerBound + rand() % (upperBound - lowerBound + 1);
  ;
}

// A given day's weather will have an effect on
// what actions the player can take and how likely they are to succeed at them
QString World::generateWeather() {
  float blizzardProb = 5;
  float snowyProb = 20;
  float cloudyProb = 50;
  int prob = rand() % 100;
  if (prob < blizzardProb && currentWeather != "snowing heavily" &&
      currentTemperature <= 12) {
    return "snowing heavily";
  } else if (prob < snowyProb) {
    return "snowing";
  } else if (prob < cloudyProb) {
    return "cloudy";
  } else {
    return "clear";
  }
}

World worldObj;

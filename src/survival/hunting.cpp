#include "../../include/survival/hunting.h"
#include "../../include/core/world.h"
#include "../../include/entities/player.h"

Hunting::Hunting() {

  bearParts = {{"BEAR FAT", 1, false, 0, 20, "FAT", "NONE",
                "I could cook it to get rendered fat."},
               {"BEAR MEAT", 1, false, 50, 20, "RAW MEAT", "NONE",
                "If cooked, it could provide a filling meal."},
               {"BEAR PELT", 1, false, 0, 20, "PELT", "NONE",
                "I could use it for crafting."}};

  deerParts = {{"DEER FAT", 1, false, 0, 20, "FAT", "NONE",
                "I could cook it to get rendered fat."},
               {"DEER MEAT", 1, false, 30, 20, "RAW MEAT", "NONE",
                "If cooked, it could ease my hunger."},
               {"DEER PELT", 1, false, 0, 20, "PELT", "NONE",
                "I could use it for crafting."}};

  foxParts = {{"FOX FAT", 1, false, 0, 20, "FAT", "NONE",
               "I could cook it to get rendered fat."},
              {"FOX MEAT", 1, false, 20, 20, "RAW MEAT", "NONE",
               "If cooked, it could provide some nourishment."},
              {"FOX PELT", 1, false, 0, 20, "PELT", "NONE",
               "I could use it for crafting."}};

  rabbitParts = {{"RABBIT FAT", 1, false, 0, 20, "FAT", "NONE",
                  "I could cook it to get rendered fat."},
                 {"RABBIT MEAT", 1, false, 15, 20, "RAW MEAT", "NONE",
                  "If cooked, it could slightly ease my hunger."},
                 {"RABBIT PELT", 1, false, 0, 20, "PELT", "NONE",
                  "I could use it for crafting."}};

  animalCarcasses = {
      {"BEAR", 1, false, 0, 100, "ANIMALS", "NONE",
       "The slain bear almost looks bigger on the ground."},
      {"DEER", 1, false, 0, 50, "ANIMALS", "NONE", "It was a lean doe."},
      {"FOX", 1, false, 0, 30, "ANIMALS", "NONE",
       "It wouldn't provide much meat."},
      {"RABBIT", 1, false, 0, 30, "ANIMALS", "NONE",
       "It would provide very little meat."}};

  validAnimals = {"BEAR", "DEER", "FOX", "RABBIT"};

  dailyAttempts = 0;
}

QString Hunting::getActiveAnimal() const { return activeAnimal; }

int Hunting::getDailyAttempts() const { return dailyAttempts; }

std::vector<Item> &Hunting::getSlainAnimals() { return animalCarcasses; }

void Hunting::setActiveAnimal(QString animal) { activeAnimal = animal; }

int Hunting::seek(QString target, int arrowIndex) {
  dailyAttempts++;
  if (std::find(validAnimals.begin(), validAnimals.end(), target) !=
      validAnimals.end()) {
    if (foundAnimal(target)) {
      activeAnimal = target;
      return ANIMAL_FOUND;
    }
    return ANIMAL_NOT_FOUND;
  }
  return ANIMAL_INVALID;
}

bool Hunting::assessDamage(QString target) {
  QMap<QString, int> probabilities = {
      {"BEAR", 80}, {"DEER", 70}, {"FOX", 60}, {"RABBIT", 70}};
  int chance = 0;
  if (probabilities.contains(target)) {
    chance = probabilities.value(target);
  }
  return worldObj.rollDice(chance);
}

bool Hunting::hitTarget(QString target) {
  QMap<QString, int> probabilities = {
      {"BEAR", 20}, {"DEER", 70}, {"FOX", 40}, {"RABBIT", 30}};
  int chance = 0;
  if (probabilities.contains(target)) {
    chance = probabilities.value(target);
  }
  return worldObj.rollDice(chance);
}

bool Hunting::recoveredArrow(bool hitTarget) {
  int chance;
  if (hitTarget) {
    chance = 30;
  } else {
    chance = 65;
  }
  if (worldObj.rollDice(chance)) {
    return true;
  }
  return false;
}

bool Hunting::skinCarcass(QString target, Location *location) {
  QMap<QString, std::vector<Item>> animalParts = {{"BEAR", bearParts},
                                                  {"DEER", deerParts},
                                                  {"FOX", foxParts},
                                                  {"RABBIT", rabbitParts}};
  if (animalParts.contains(target)) {
    return inventoryObj.addLoot(playerObj.getInventory(),
                                location->getInventory(),
                                animalParts.value(target));
  }
  return false;
}

void Hunting::resetDailyAttempts() { dailyAttempts = 0; }

bool Hunting::foundAnimal(QString target) {
  QMap<QString, int> probabilities = {
      {"BEAR", 5}, {"DEER", 40}, {"FOX", 20}, {"RABBIT", 35}};
  int chance;
  if (probabilities.contains(target)) {
    chance = probabilities.value(target);
  }
  if (worldObj.rollDice(chance)) {
    return true;
  }
  return false;
}

Hunting huntingObj;

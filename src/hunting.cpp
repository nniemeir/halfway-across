#include "../include/hunting.h"
#include "../include/player.h"
#include "../include/world.h"

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

  slainAnimals = {
      {"BEAR", 1, false, 0, 100, "ANIMALS", "NONE",
       "The slain bear almost looks bigger on the ground."},
      {"DEER", 1, false, 0, 50, "ANIMALS", "NONE", "It was a lean doe."},
      {"FOX", 1, false, 0, 30, "ANIMALS", "NONE",
       "It wouldn't provide much meat."},
      {"RABBIT", 1, false, 0, 30, "ANIMALS", "NONE",
       "It would provide very little meat."}};

  validAnimals = {"BEAR", "DEER", "FOX", "RABBIT"};

  dailyHunts = 0;
}

QString Hunting::getActiveAnimal() const { return activeAnimal; }

int Hunting::getDailyHunts() const { return dailyHunts; }

std::vector<Item> &Hunting::getSlainAnimals() { return slainAnimals; }

void Hunting::setActiveAnimal(QString animal) { activeAnimal = animal; }

int Hunting::activity(QString target, int arrowIndex) {
  dailyHunts++;
  if (std::find(validAnimals.begin(), validAnimals.end(), target) !=
      validAnimals.end()) {
    if (foundAnimal(target)) {
      activeAnimal = target;
      return ANIMAL_FOUND;
    } else {
      return ANIMAL_NOT_FOUND;
    }
  } else {
    return ANIMAL_INVALID;
  }
}

bool Hunting::assessDamage(QString target) {
  QMap<QString, int> probabilities = {
      {"BEAR", 80}, {"DEER", 70}, {"FOX", 60}, {"RABBIT", 70}};
  int chance = 0;
  if (probabilities.contains(target)) {
    chance = probabilities.value(target);
  }
  return worldObj.roll(chance);
}

bool Hunting::hitTarget(QString target) {
  QMap<QString, int> probabilities = {
      {"BEAR", 20}, {"DEER", 70}, {"FOX", 40}, {"RABBIT", 30}};
  int chance = 0;
  if (probabilities.contains(target)) {
    chance = probabilities.value(target);
  }
  return worldObj.roll(chance);
}

bool Hunting::recoveredArrow(bool hitTarget) {
  int chance;
  if (hitTarget) {
    chance = 30;
  } else {
    chance = 65;
  }
  if (worldObj.roll(chance)) {
    return true;
  } else {
    return false;
  }
}

bool Hunting::skinAnimal(QString target, Location *location) {
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

void Hunting::resetDailyHunts() { dailyHunts = 0; }

bool Hunting::foundAnimal(QString target) {
  QMap<QString, int> probabilities = {
      {"BEAR", 5}, {"DEER", 40}, {"FOX", 20}, {"RABBIT", 35}};
  int chance;
  if (probabilities.contains(target)) {
    chance = probabilities.value(target);
  }
  if (worldObj.roll(chance)) {
    return true;
  } else {
    return false;
  }
}

Hunting huntingObj;

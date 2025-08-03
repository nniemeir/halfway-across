#include "survival/hunting.h"
#include "core/audio.h"
#include "core/handling/inputhandler.h"
#include "core/world.h"
#include "entities/player.h"

Hunting::Hunting() {
  dailyAttempts = 0;

  animalCarcasses = {
      {"BEAR", "The slain bear almost looks bigger on the ground.", "ANIMALS",
       "NONE", 1, false, 0, 100},
      {"DEER", "It was a lean doe.", "ANIMALS", "NONE", 1, false, 0, 50},
      {"FOX", "It wouldn't provide much meat.", "ANIMALS", "NONE", 1, false, 0,
       30},
      {"RABBIT", "It would provide very little meat.", "ANIMALS", "NONE", 1,
       false, 0, 30}};

  validAnimals = {"BEAR", "DEER", "FOX", "RABBIT"};

  bearParts = {{"BEAR FAT", "I could cook it to get rendered fat.", "FAT",
                "NONE", 1, false, 0, 20},
               {"BEAR MEAT", "If cooked, it could provide a filling meal.",
                "RAW MEAT", "NONE", 1, false, 50, 20},
               {"BEAR PELT", "I could use it for crafting.", "PELT", "NONE", 1,
                false, 0, 20}};

  deerParts = {{"DEER FAT", "I could cook it to get rendered fat.", "FAT",
                "NONE", 1, false, 0, 20},
               {"DEER MEAT", "If cooked, it could ease my hunger.", "RAW MEAT",
                "NONE", 1, false, 30, 20},
               {"DEER PELT", "I could use it for crafting.", "PELT", "NONE", 1,
                false, 0, 20}};

  foxParts = {{"FOX FAT", "I could cook it to get rendered fat.", "FAT", "NONE",
               1, false, 0, 20},
              {"FOX MEAT", "If cooked, it could provide some nourishment.",
               "RAW MEAT", "NONE", 1, false, 20, 20},
              {"FOX PELT", "I could use it for crafting.", "PELT", "NONE", 1,
               false, 0, 20}};

  rabbitParts = {{"RABBIT FAT", "I could cook it to get rendered fat.", "FAT",
                  "NONE", 1, false, 0, 20},
                 {"RABBIT MEAT", "If cooked, it could slightly ease my hunger.",
                  "RAW MEAT", "NONE", 1, false, 15, 20},
                 {"RABBIT PELT", "I could use it for crafting.", "PELT", "NONE",
                  1, false, 0, 20}};
}

QString Hunting::getActiveAnimal() const { return activeAnimal; }

int Hunting::getDailyAttempts() const { return dailyAttempts; }

std::vector<Item> &Hunting::getSlainAnimals() { return animalCarcasses; }

void Hunting::setActiveAnimal(QString animal) { activeAnimal = animal; }

void Hunting::resetDailyAttempts() { dailyAttempts = 0; }

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

QString Hunting::processSeekResult(MainWindow *mainWindow, QString target, int arrowIndex) {
  int result = huntingObj.seek(target, arrowIndex);
  QString resultMsg;
  switch (result) {
  case Hunting::ANIMAL_FOUND:
    mainWindow->playSfx("qrc:/audio/sfx/hunt.mp3");
    huntingObj.setActiveAnimal(target);
    resultMsg = QString("I spotted %1 %2.")
                    .arg(inputHandlerObj.getArticle(target), target.toLower());
    break;
  case Hunting::ANIMAL_NOT_FOUND:
    resultMsg = QString("I was unable to find %1 %2 in the valley.")
                    .arg(inputHandlerObj.getArticle(target), target.toLower());
    break;
  case Hunting::ANIMAL_INVALID:
    resultMsg =
        QString("I thought of hunting %1, but it didn't seem reasonable in "
                "the area.")
            .arg(target.toLower());
    break;
  }
  return resultMsg;
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

bool Hunting::assessDamage(QString target) {
  QMap<QString, int> probabilities = {
      {"BEAR", 80}, {"DEER", 70}, {"FOX", 60}, {"RABBIT", 70}};
  int chance = 0;
  if (probabilities.contains(target)) {
    chance = probabilities.value(target);
  }
  return worldObj.rollDice(chance);
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

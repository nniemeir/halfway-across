#include "survival/fishing.h"
#include "core/handling/verbhandler.h"
#include "entities/player.h"
#include "items/inventory.h"

Fishing::Fishing()
    : fish{{"CUTTHROAT TROUT",
            "It was a common fish that could be eaten if I cooked it.",
            "RAW MEAT", "NONE", 1, false, 25, 10},
           {"BROOK TROUT",
            "It was a fairly common fish that could be eaten if I cooked it.",
            "RAW MEAT", "NONE", 1, false, 25, 10},
           {"RAINBOW TROUT",
            "It was an uncommon fish that could be eaten if I cooked it.",
            "RAW MEAT", "NONE", 1, false, 30, 10},
           {"BROWN TROUT",
            "It was a rare fish that could be eaten if I cooked it.",
            "RAW MEAT", "NONE", 1, false, 35, 10}},
      dailyAttempts(0) {}

int Fishing::getDailyAttempts() const { return dailyAttempts; }

std::vector<Item> &Fishing::getInventory() { return fish; }

QString Fishing::rollforFish() {
  dailyAttempts++;
  static const float brownTroutProb = 5;
  static const float brookTroutProb = 10;
  static const float nothingProb = 15;
  static const float rainbowTroutProb = 20;
  static const float cutthroatProb = 50;

  int prob = rand() % 100;
  if (prob < brownTroutProb) {
    return "BROWN TROUT";
  } else if (prob < brownTroutProb + brookTroutProb) {
    return "BROOK TROUT";
  } else if (prob < brownTroutProb + brookTroutProb + nothingProb) {
    return "NOTHING";
  } else if (prob <
             brownTroutProb + brookTroutProb + nothingProb + rainbowTroutProb) {
    return "RAINBOW TROUT";
  } else {
    return "CUTTHROAT TROUT";
  }
}

QString Fishing::seek() {
  QString generatedFish = rollforFish();
  if (generatedFish == "NOTHING") {
      return "I waited a while but nothing was biting so I reeled in the line.";
  }
    int fishIndex = inventoryObj.searchInventory(getInventory(), generatedFish);
      int playerItemIndex =
          inventoryObj.searchInventory(playerObj.getInventory(), generatedFish);
      inventoryObj.addItem(
          playerObj.getInventory(),
          inventoryObj.getInventoryItem(getInventory(), fishIndex),
          playerItemIndex);
      return QString("I caught a %1!\n")
          .arg(inventoryObj.getInventoryItem(getInventory(), fishIndex)
                   .getName()
                   .toLower());
}

void Fishing::resetDailyAttempts() { dailyAttempts = 0; }

Fishing fishingObj;

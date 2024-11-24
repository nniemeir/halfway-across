#include "../../include/survival/fishing.h"
#include "../../include/core/handling/verbhandler.h"
#include "../../include/entities/player.h"
#include "../../include/items/inventory.h"

Fishing::Fishing()
    : fish{{"CUTTHROAT TROUT", 1, false, 25, 10, "RAW MEAT", "NONE",
            "It was a common fish that could be eaten if I cooked it."},
           {"BROOK TROUT", 1, false, 25, 10, "RAW MEAT", "NONE",
            "It was a fairly common fish that could be eaten if I cooked it."},
           {"RAINBOW TROUT", 1, false, 30, 10, "RAW MEAT", "NONE",
            "It was an uncommon fish that could be eaten if I cooked it."},
           {"BROWN TROUT", 1, false, 35, 10, "RAW MEAT", "NONE",
            "It was a rare fish that could be eaten if I cooked it."}},
      dailyAttempts(0) {}

int Fishing::getDailyAttempts() const { return dailyAttempts; }

std::vector<Item> &Fishing::getInventory() { return fish; }

QString Fishing::seek() {
  QString generatedFish = rollforFish();
  if (generatedFish != "NOTHING") {
    int fishIndex = inventoryObj.searchInventory(getInventory(), generatedFish);
    if (fishIndex != VerbHandler::ITEM_NOT_FOUND) {
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
  }
  return "I waited a while but nothing was biting so I reeled in the line.";
}

QString Fishing::rollforFish() {
  dailyAttempts++;
  float brownTroutProb = 5;
  float brookTroutProb = 10;
  float nothingProb = 15;
  float rainbowTroutProb = 20;
  float cutthroatProb = 50;
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

void Fishing::resetDailyAttempts() { dailyAttempts = 0; }

Fishing fishingObj;

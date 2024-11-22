#include "../../include/core/handling.h"
#include "../../include/entities/player.h"
#include "../../include/items/inventory.h"
#include "../../include/survival/fishing.h"

Fishing::Fishing()
    : fish{{"CUTTHROAT TROUT", 1, false, 25, 10, "RAW MEAT", "NONE",
            "It was a common fish that could be eaten if I cooked it."},
           {"BROOK TROUT", 1, false, 25, 10, "RAW MEAT", "NONE",
            "It was a fairly common fish that could be eaten if I cooked it."},
           {"RAINBOW TROUT", 1, false, 30, 10, "RAW MEAT", "NONE",
            "It was an uncommon fish that could be eaten if I cooked it."},
           {"BROWN TROUT", 1, false, 35, 10, "RAW MEAT", "NONE",
            "It was a rare fish that could be eaten if I cooked it."}},
      dailyFished(0) {}

int Fishing::getDailyFished() const { return dailyFished; }

std::vector<Item> &Fishing::getFishInventory() { return fish; }

QString Fishing::activity(int rodIndex) {
  QString generatedFish = fishingObj.generateFish();
  if (generatedFish != "NOTHING") {
    int fishIndex = inventoryObj.searchInventory(fishingObj.getFishInventory(),
                                                 generatedFish);
    if (fishIndex != Handling::ITEM_NOT_FOUND) {
      int playerItemIndex =
          inventoryObj.searchInventory(playerObj.getInventory(), generatedFish);
      inventoryObj.addItem(playerObj.getInventory(),
                           inventoryObj.getInventoryItem(
                               fishingObj.getFishInventory(), fishIndex),
                           playerItemIndex);
      return QString("I caught a %1!\n")
          .arg(inventoryObj
                   .getInventoryItem(fishingObj.getFishInventory(), fishIndex)
                   .getName()
                   .toLower());
    }
  }
  return "I waited a while but nothing was biting so I reeled in the line.";
}

QString Fishing::generateFish() {
  dailyFished++;
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

void Fishing::resetDailyFished() { dailyFished = 0; }

Fishing fishingObj;

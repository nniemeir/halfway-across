#include "../../include/items/inventory.h"
#include "../../include/core/handling/verbhandler.h"
#include "../../include/entities/player.h"

Item &Inventory::getInventoryItem(std::vector<Item> &inventory,
                                  const int index) {
  return inventory[index];
}

int Inventory::searchInventory(std::vector<Item> &inventory,
                               const QString &itemName) const {
  auto it =
      std::find_if(inventory.begin(), inventory.end(),
                   [&](const Item &i) { return i.getName() == itemName; });

  if (it != inventory.end()) {
    return std::distance(inventory.begin(), it);
  }
  return VerbHandler::ITEM_NOT_FOUND;
}

void Inventory::addItem(std::vector<Item> &inventory, Item itemToAdd,
                        const int itemIndex) {
  if (itemIndex == VerbHandler::ITEM_NOT_FOUND) {
    itemToAdd.setAmount(1);
    inventory.push_back(itemToAdd);
    return;
  }
  inventory[itemIndex].setAmount(inventory[itemIndex].getAmount() +
                                 itemToAdd.getAmount());
}

bool Inventory::addLoot(std::vector<Item> &inventory,
                        std::vector<Item> &locationInventory,
                        const std::vector<Item> itemList) {
  bool fitAll = true;
  for (const auto &item : itemList) {
    int playerItemIndex = searchInventory(inventory, item.getName());
    int locationIndex = searchInventory(locationInventory, item.getName());
    if (fitsInventory(inventory, item)) {
      addItem(inventory, item, playerItemIndex);
      continue;
    }
    addItem(locationInventory, getInventoryItem(inventory, playerItemIndex),
            locationIndex);
    fitAll = false;
  }
  return fitAll;
}

bool Inventory::fitsInventory(const std::vector<Item> &inventory,
                              const Item &itemToAdd) {
  int currentInventoryWeight = 0;
  int totalItemWeight = 0;
  for (const auto &item : inventory) {
    totalItemWeight = item.getAmount() * item.getWeight();
    currentInventoryWeight = currentInventoryWeight + totalItemWeight;
  }
  if (currentInventoryWeight + itemToAdd.getWeight() <= INVENTORY_CAPACITY) {
    return true;
  }
  return false;
}

void Inventory::removeItem(std::vector<Item> &inventory, const int itemIndex) {
  if (inventory[itemIndex].getAmount() <= 1) {
    inventory.erase(inventory.begin() + itemIndex);
    return;
  }
  inventory[itemIndex].setAmount(inventory[itemIndex].getAmount() - 1);
}

void Inventory::deactivateLocationSpecificItems() {
  int rodIndex = searchInventory(playerObj.getInventory(), "FISHING ROD");
  if (rodIndex != VerbHandler::ITEM_NOT_FOUND) {
    getInventoryItem(playerObj.getInventory(), rodIndex).setActive(false);
  }
}

Inventory inventoryObj;

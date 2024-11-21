#include "../include/inventory.h"
#include "../include/handling.h"

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
    int index = std::distance(inventory.begin(), it);
    return index;
  } else {
    return Handling::ITEM_NOT_FOUND;
  }
}

void Inventory::addItem(std::vector<Item> &inventory, Item itemToAdd,
                        const int itemIndex) {
  if (itemIndex == Handling::ITEM_NOT_FOUND) {
    itemToAdd.setQuantity(1);
    inventory.push_back(itemToAdd);
  } else {
    inventory[itemIndex].setQuantity(inventory[itemIndex].getAmount() +
                                     itemToAdd.getAmount());
  }
}

bool Inventory::addLoot(std::vector<Item> &inventory,
                        std::vector<Item> &locationInventory,
                        const std::vector<Item> itemList) {
  bool fitAll = true;
  for (const auto &item : itemList) {
    int playerItemIndex =
        inventoryObj.searchInventory(inventory, item.getName());
    int locationIndex =
        inventoryObj.searchInventory(locationInventory, item.getName());
    if (fitsInventory(inventory, item)) {
      inventoryObj.addItem(inventory, item, playerItemIndex);
    } else {
      inventoryObj.addItem(
          locationInventory,
          inventoryObj.getInventoryItem(inventory, playerItemIndex),
          locationIndex);
      fitAll = false;
    }
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
  } else {
    return false;
  }
}

void Inventory::removeItem(std::vector<Item> &inventory, const int itemIndex) {
  if (inventory[itemIndex].getAmount() <= 1) {
    inventory.erase(inventory.begin() + itemIndex);
  } else {
    inventory[itemIndex].setQuantity(inventory[itemIndex].getAmount() - 1);
  }
}

Inventory inventoryObj;

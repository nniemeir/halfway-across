#include "../include/inventory.h"

Inventory inventoryObj;

// Since verb handling often involves checking if the player has a given item in
// their inventory, this will be altered later to
// use a hash table for the sake of performance
int Inventory::searchInventory(std::vector<item> &inventory,
                               const QString &itemName) const {
  auto it = std::find_if(inventory.begin(), inventory.end(),
                         [&](const item &i) { return i.name == itemName; });

  if (it != inventory.end()) {
    int index = std::distance(inventory.begin(), it);
    return index;
  } else {
    return -1;
  }
}

const item &Inventory::getInventoryItem(std::vector<item> &inventory,
                                        int index) const {
  return inventory[index];
}

void Inventory::addItem(std::vector<item> &inventory, const item itemToAdd,
                        int itemIndex) {
  if (itemIndex == -1) {
    inventory.push_back(itemToAdd);
  } else {
    setItemQuantity(inventory, itemIndex,
                    getItemQuantity(inventory, itemIndex) + 1);
  }
}

void Inventory::removeItem(std::vector<item> &inventory, int itemIndex) {
  if (getItemQuantity(inventory, itemIndex) <= 1) {
    inventory.erase(inventory.begin() + itemIndex);
  } else {
    setItemQuantity(inventory, itemIndex,
                    getItemQuantity(inventory, itemIndex) - 1);
  }
}

QString Inventory::getItemName(std::vector<item> &inventory, int index) const {
  return inventory[index].name;
}

QString Inventory::getItemPayload(std::vector<item> &inventory,
                                  int index) const {
  return inventory[index].payload;
}

int Inventory::getItemEquipped(std::vector<item> &inventory, int index) const {
  return inventory[index].active;
}

int Inventory::getItemEffect(std::vector<item> &inventory, int index) const {
  return inventory[index].effects;
}

void Inventory::setItemEffect(std::vector<item> &inventory, int index,
                              int value) {
  inventory[index].effects = value;
}

void Inventory::setItemEquipped(std::vector<item> &inventory, int index,
                                int value) {
  inventory[index].active = value;
}

int Inventory::getItemQuantity(std::vector<item> &inventory, int index) const {
  return inventory[index].amount;
}

void Inventory::setItemQuantity(std::vector<item> &inventory, int index,
                                int value) {
  inventory[index].amount = value;
}

QString Inventory::getItemType(std::vector<item> &inventory, int index) const {
  return inventory[index].type;
}

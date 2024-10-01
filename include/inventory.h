#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
class Inventory {
public:
  Inventory(){};
  Item &getInventoryItem(std::vector<Item> &inventory, const int index);
  int searchInventory(std::vector<Item> &inventory,
                      const QString &ItemName) const;
  void addItem(std::vector<Item> &inventory, const Item ItemToAdd,
               const int ItemIndex);
  bool addLoot(std::vector<Item> &inventory,
               std::vector<Item> &locationInventory,
               const std::vector<Item> itemList);
  bool fitsInventory(const std::vector<Item> &inventory, const Item &itemToAdd);
  void removeItem(std::vector<Item> &inventory, const int index);

private:
  const int INVENTORY_CAPACITY = 100;
};

extern Inventory inventoryObj;

#endif

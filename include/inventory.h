#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
class Inventory {
public:
  Inventory(){};
  int searchInventory(std::vector<Item> &inventory,
                      const QString &ItemName) const;
  Item &getInventoryItem(std::vector<Item> &inventory, int index);
  void addItem(std::vector<Item> &inventory, const Item ItemToAdd,
               int ItemIndex);
  void removeItem(std::vector<Item> &inventory, int index);
};

extern Inventory inventoryObj;

#endif // INVENTORY_H

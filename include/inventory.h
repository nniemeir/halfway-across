#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
class Inventory {
public:
    Inventory() {};
    int searchInventory(std::vector<item> &inventory, const QString &itemName) const;
    const item &getInventoryItem(std::vector<item> &inventory, int index) const;
    void addItem(std::vector<item> &inventory, const item itemToAdd, int itemIndex);
    void removeItem(std::vector<item> &inventory, int index);
    QString getItemName(std::vector<item> &inventory, int index) const;
    int getItemEffect(std::vector<item> &inventory, int index) const;
    int getItemEquipped(std::vector<item> &inventory, int index) const;
    void setItemEquipped(std::vector<item> &inventory, int index, int value);
    int getItemQuantity(std::vector<item> &inventory, int index) const;
    void setItemQuantity(std::vector<item> &inventory, int index, int value);
    QString getItemType(std::vector<item> &inventory, int index) const;
};

extern Inventory inventoryObj;


#endif // INVENTORY_H

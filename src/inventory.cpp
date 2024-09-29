#include "../include/inventory.h"

Inventory inventoryObj;

int Inventory::searchInventory(std::vector<Item> &inventory,
                               const QString &itemName) const
{
  auto it =
      std::find_if(inventory.begin(), inventory.end(),
                   [&](const Item &i)
                   { return i.getName() == itemName; });

  if (it != inventory.end())
  {
    int index = std::distance(inventory.begin(), it);
    return index;
  }
  else
  {
    return -1;
  }
}

Item &Inventory::getInventoryItem(std::vector<Item> &inventory, int index)
{
  return inventory[index];
}

void Inventory::addItem(std::vector<Item> &inventory, Item itemToAdd,
                        int itemIndex)
{
  if (itemIndex == -1)
  {
    itemToAdd.setQuantity(1);
    inventory.push_back(itemToAdd);
  }
  else
  {
    inventory[itemIndex].setQuantity(inventory[itemIndex].getAmount() +
                                     itemToAdd.getAmount());
  }
}

void Inventory::addLoot(std::vector<Item> &inventory, std::vector<Item> itemList)
{
  for (const auto &item : itemList)
  {
    int itemIndex =
        inventoryObj.searchInventory(inventory, item.getName());
    inventoryObj.addItem(inventory,
                         item,
                         itemIndex);
  }
}

void Inventory::removeItem(std::vector<Item> &inventory, int itemIndex)
{
  if (inventory[itemIndex].getAmount() <= 1)
  {
    inventory.erase(inventory.begin() + itemIndex);
  }
  else
  {
    inventory[itemIndex].setQuantity(inventory[itemIndex].getAmount() - 1);
  }
}

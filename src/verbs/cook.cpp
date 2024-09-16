#include "../../include/handling.h"
#include "../../include/item.h"
#include "../../include/player.h"

void Handling::cook(MainWindow *mainWindow, QString target,
                    Location *location) {
  if (location->getName() == "camp") {
    int itemIndex = inventoryObj.searchInventory(player.getInventory(), target);
    if (itemIndex != -1) {
      if (inventoryObj.getItemType(player.getInventory(), itemIndex) ==
          "RAW MEAT") {
        mainWindow->setDescription(
            QString("I cooked the %1.").arg(target.toLower()));
        item cooker;
        item cookedItem = cooker.cookMeat(
            inventoryObj.getInventoryItem(player.getInventory(), itemIndex));
        inventoryObj.removeItem(player.getInventory(), itemIndex);
        int cookedIndex = inventoryObj.searchInventory(player.getInventory(),
                                                       cookedItem.name);
        inventoryObj.addItem(player.getInventory(), cookedItem, cookedIndex);
      } else if (inventoryObj.getItemType(player.getInventory(), itemIndex) ==
                 "FAT") {
        mainWindow->setDescription(
            QString("I rendered the %1.").arg(target.toLower()));
        inventoryObj.removeItem(player.getInventory(), itemIndex);
        int fatIndex = inventoryObj.searchInventory(player.getInventory(),
                                                    "RENDERED FAT");
        inventoryObj.addItem(player.getInventory(),
                             {"RENDERED FAT", 1, 1, 10, "ANIMAL FAT", "NONE"},
                             fatIndex);
      } else {
        mainWindow->setDescription("I couldn't cook that.");
      }
    } else {
      mainWindow->setDescription(
          QString("I didn't have any %1.").arg(target.toLower()));
    }
  } else {
    mainWindow->setDescription("I needed to be near a campfire to cook.");
  }
}

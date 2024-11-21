#include "../../include/handling.h"
#include "../../include/item.h"
#include "../../include/player.h"

void Handling::cook(MainWindow *mainWindow, QString target,
                    Location *location) {
  if (location->getName() == "Camp") {
    int itemIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), target);
    if (itemIndex != ITEM_NOT_FOUND) {
      if (inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
              .getType() == "RAW MEAT") {
        mainWindow->setDescription(
            QString("I cooked some %1 over the fire.").arg(target.toLower()));
        Item cooker;
        Item cookedItem = cooker.cookMeat(
            inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex));
        inventoryObj.removeItem(playerObj.getInventory(), itemIndex);
        int cookedIndex = inventoryObj.searchInventory(playerObj.getInventory(),
                                                       cookedItem.getName());
        inventoryObj.addItem(playerObj.getInventory(), cookedItem, cookedIndex);
      } else if (inventoryObj
                     .getInventoryItem(playerObj.getInventory(), itemIndex)
                     .getType() == "FAT") {
        mainWindow->setDescription(
            QString("I rendered the %1.").arg(target.toLower()));
        inventoryObj.removeItem(playerObj.getInventory(), itemIndex);
        int fatIndex = inventoryObj.searchInventory(playerObj.getInventory(),
                                                    "RENDERED FAT");
        inventoryObj.addItem(
            playerObj.getInventory(),
            {"RENDERED FAT", 1, false, 10, 0, "ANIMAL FAT", "NONE",
             "I could use it for crafting or as fishing bait."},
            fatIndex);
      } else {
        mainWindow->setDescription(
            QString("I thought of cooking %1 %2, but dismissed the idea.")
                .arg(handlingObj.getArticle(target), target.toLower()));
      }
    } else {
      missingItemMsg(mainWindow, getArticle(target) + " " + target);
    }
  } else {
    mainWindow->setDescription("I needed to be near a campfire to cook.");
  }
}

#include "../../../include/core/handling/inputhandler.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"
#include "../../../include/items/item.h"

void VerbHandler::cook(MainWindow *mainWindow, QString target,
                    Location *location) {
  if (location->getName() != "Camp") {
    mainWindow->setDescription("I needed to be near a campfire to cook.");
  }

  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (itemIndex == ITEM_NOT_FOUND) {
    msgHandlerObj.missingItemMsg(mainWindow, inputHandlerObj.getArticle(target) + " " + target);
    return;
  }

  QString itemType = playerObj.getInventoryItem(playerObj.getInventory(), itemIndex).getType();
  if (itemType != "RAW MEAT" && itemType != "FAT") {
      mainWindow->setDescription(
      QString("I thought of cooking %1 %2, but dismissed the idea.")
          .arg(inputHandlerObj.getArticle(target), target.toLower()));
      return;
  }

  if (itemType == "RAW MEAT") {
    mainWindow->setDescription(
        QString("I cooked some %1 over the fire.").arg(target.toLower()));
    Item cooker;
    Item cookedItem = cooker.cookMeat(
        inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex));
    inventoryObj.removeItem(playerObj.getInventory(), itemIndex);
    int cookedItemIndex = inventoryObj.searchInventory(playerObj.getInventory(),
                                                   cookedItem.getName());
    inventoryObj.addItem(playerObj.getInventory(), cookedItem, cookedItemIndex);
    return;
  }

  if (itemType == "FAT") {
    mainWindow->setDescription(
        QString("I rendered the %1.").arg(target.toLower()));
    inventoryObj.removeItem(playerObj.getInventory(), itemIndex);
    int renderedFatIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), "RENDERED FAT");
    inventoryObj.addItem(playerObj.getInventory(),
                         {"RENDERED FAT", 1, false, 10, 0, "ANIMAL FAT", "NONE",
                          "I could use it for crafting or as fishing bait."},
                         renderedFatIndex);
    return;
  }
}

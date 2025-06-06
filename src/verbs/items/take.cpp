#include "../../../include/core/handling/inputhandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"
#include "../../../include/items/inventory.h"

void VerbHandler::take(MainWindow *mainWindow, QString target,
                       Location *location) {
  int itemIndex =
      inventoryObj.searchInventory(location->getInventory(), target);
  if (itemIndex == ITEM_NOT_FOUND) {
    mainWindow->setDescription(
        QString("There wasn't %1 %2 there.")
            .arg(inputHandlerObj.getArticle(target), target.toLower()));
    return;
  }
  QString itemName =
      inventoryObj.getInventoryItem(location->getInventory(), itemIndex)
          .getName()
          .toLower();
  mainWindow->setDescription(
      QString("I took %1 %2.")
          .arg(inputHandlerObj.getArticle(itemName), itemName));
  int playerItemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  Item toAdd =
      inventoryObj.getInventoryItem(location->getInventory(), itemIndex);
  if (!inventoryObj.fitsInventory(playerObj.getInventory(), toAdd)) {
    mainWindow->setDescription(
        QString("I didn't have enough space to take %1 %2 with me.")
            .arg(inputHandlerObj.getArticle(target), target.toLower()));
  }
  mainWindow->playSfx("qrc:/audio/sfx/take.mp3");
  inventoryObj.addItem(
      playerObj.getInventory(),
      inventoryObj.getInventoryItem(location->getInventory(), itemIndex),
      playerItemIndex);
  inventoryObj.removeItem(location->getInventory(), itemIndex);
}

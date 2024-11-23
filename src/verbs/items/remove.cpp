#include "../../../include/core/handling/inputhandler.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"

void VerbHandler::remove(MainWindow *mainWindow, QString target) {
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (itemIndex == ITEM_NOT_FOUND) {
    msgHandlerObj.missingItemMsg(mainWindow, inputHandlerObj.getArticle(target) + " " + target);
    return;
  }
  if (!inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .getActive()) {
    mainWindow->setDescription(
        QString("I was not wearing my %1.").arg(target.toLower()));
    return;
  }
  inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
      .setActive(false);
  playerObj.setWarmth(
      playerObj.getWarmth() -
      inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .getEffect());
  mainWindow->setDescription(QString("I removed my %1.").arg(target.toLower()));
}

#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"

void Handling::wear(MainWindow *mainWindow, QString target) {
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (itemIndex != ITEM_NOT_FOUND) {
    if (!inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
             .getActive()) {
      inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .setActive(true);
      playerObj.setWarmth(
          playerObj.getWarmth() +
          inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
              .getEffect());
      mainWindow->setDescription(
          QString("I put on my %1.").arg(target.toLower()));
    } else {
      mainWindow->setDescription(
          QString("I was already wearing my %1.").arg(target.toLower()));
    }
  } else {
    missingItemMsg(mainWindow, getArticle(target) + " " + target);
  }
}

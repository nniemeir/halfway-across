#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"

void Handling::remove(MainWindow *mainWindow, QString target) {
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (itemIndex != ITEM_NOT_FOUND) {
    if (inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
            .getActive()) {
      inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .setActive(false);
      playerObj.setWarmth(
          playerObj.getWarmth() -
          inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
              .getEffect());
      mainWindow->setDescription(
          QString("I removed my %1.").arg(target.toLower()));
    } else {
      mainWindow->setDescription(
          QString("I was not wearing my %1.").arg(target.toLower()));
    }
  } else {
    missingItemMsg(mainWindow, getArticle(target) + " " + target);
  }
}

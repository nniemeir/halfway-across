#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::wear(MainWindow *mainWindow, QString target) {
  int index = inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (index != -1) {
    if (inventoryObj.getInventoryItem(playerObj.getInventory(), index)
            .getActive() == 0) {
      inventoryObj.getInventoryItem(playerObj.getInventory(), index)
          .setActive(1);
      playerObj.setWarmth(
          playerObj.getWarmth() +
          inventoryObj.getInventoryItem(playerObj.getInventory(), index)
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

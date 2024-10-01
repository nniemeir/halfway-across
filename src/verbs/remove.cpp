#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::remove(MainWindow *mainWindow, QString target) {
  int targetIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (targetIndex != -1) {
    if (inventoryObj.getInventoryItem(playerObj.getInventory(), targetIndex)
            .getActive() == 1) {
      inventoryObj.getInventoryItem(playerObj.getInventory(), targetIndex)
          .setActive(0);
      playerObj.setWarmth(
          playerObj.getWarmth() -
          inventoryObj.getInventoryItem(playerObj.getInventory(), targetIndex)
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

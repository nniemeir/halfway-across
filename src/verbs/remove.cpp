#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::remove(MainWindow *mainWindow, QString target) {
  int targetIndex = inventoryObj.searchInventory(player.getInventory(), target);
  if (targetIndex != -1) {
    if (inventoryObj.getInventoryItem(player.getInventory(), targetIndex)
            .getActive() == 1) {
      inventoryObj.getInventoryItem(player.getInventory(), targetIndex)
          .setActive(0);
      player.setWarmth(
          player.getWarmth() -
          inventoryObj.getInventoryItem(player.getInventory(), targetIndex)
              .getEffect());
      mainWindow->setDescription(
          QString("I removed my %1.").arg(target.toLower()));
    } else {
      mainWindow->setDescription(
          QString("I was not wearing my %1.").arg(target.toLower()));
    }
  } else {
    mainWindow->setDescription(QString("I did not have %1 %2.")
                                   .arg(handle.getArticle(target))
                                   .arg(target.toLower()));
  }
}

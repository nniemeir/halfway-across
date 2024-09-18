#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::wear(MainWindow *mainWindow, QString target) {
  int index = inventoryObj.searchInventory(player.getInventory(), target);
  if (index != -1) {
    if (inventoryObj.getInventoryItem(player.getInventory(), index).getActive() == 0) {
      inventoryObj.getInventoryItem(player.getInventory(), index).setActive(1);
      player.setWarmth(player.getWarmth() + inventoryObj.getInventoryItem(player.getInventory(), index).getEffect());
      mainWindow->setDescription(
          QString("I put on my %1.").arg(target.toLower()));
    } else {
      mainWindow->setDescription(
          QString("I was already wearing my %1.").arg(target.toLower()));
    }
  } else {
      mainWindow->setDescription(QString("I didn't have %1 %2 to put on.").arg(handle.getArticle(target)).arg(target.toLower()));
  }
}

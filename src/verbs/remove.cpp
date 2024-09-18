#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::remove(MainWindow *mainWindow, QString target) {
  int index = inventoryObj.searchInventory(player.getInventory(), target);
  if (index != -1) {
    if (inventoryObj.getInventoryItem(player.getInventory(), index).getActive() == 1) {
          inventoryObj.getInventoryItem(player.getInventory(), index).setActive(0);
        player.setWarmth(player.getWarmth() - inventoryObj.getInventoryItem(player.getInventory(), index).getEffect());
      mainWindow->setDescription(
          QString("I removed my %1.").arg(target.toLower()));
    } else {
      mainWindow->setDescription(
          QString("I was not wearing my %1.").arg(target.toLower()));
    }
  } else {
      mainWindow->setDescription(QString("I did not have %1 %2.").arg(handle.getArticle(target)).arg(target.toLower()));
  }
}

#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::remove(MainWindow *mainWindow, QString target) {
  int index = inventoryObj.searchInventory(player.getInventory(), target);
  if (index != -1) {
    if (inventoryObj.getItemEquipped(player.getInventory(), index) == 1) {
      inventoryObj.setItemEquipped(player.getInventory(), index, 0);
      player.setWarmth(player.getWarmth() - inventoryObj.getItemEffect(player.getInventory(), index));
      mainWindow->setDescription(
          QString("You remove your %1.").arg(target.toLower()));
    } else {
      mainWindow->setDescription(
          QString("You are not wearing your %1.").arg(target.toLower()));
    }
  } else {
    mainWindow->setDescription("You do not possess that.");
  }
}

#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::load(MainWindow *mainWindow, QString target) {
  int targetIndex = inventoryObj.searchInventory(player.getInventory(), target);
  if (targetIndex != -1) {
    QString payload =
        inventoryObj.getItemPayload(player.getInventory(), targetIndex);
    int payloadIndex =
        inventoryObj.searchInventory(player.getInventory(), payload);
    if (payloadIndex != -1) {
      mainWindow->setDescription(QString("I loaded the %1 into the %2.")
                                     .arg(payload.toLower())
                                     .arg(target.toLower()));
      inventoryObj.removeItem(player.getInventory(), payloadIndex);
      inventoryObj.setItemEffect(player.getInventory(), targetIndex, 100);
    } else {
      mainWindow->setDescription(
          QString("I needed a %1.").arg(payload.toLower()));
    }
  } else {
    mainWindow->setDescription(
        QString("I didn't have a %1.").arg(target.toLower()));
  }
}

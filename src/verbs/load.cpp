#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::load(MainWindow *mainWindow, QString target) {
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (itemIndex != ITEM_NOT_FOUND) {
    QString payloadName =
        inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
            .getPayload();
    int payloadIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), payloadName);
    if (payloadIndex != ITEM_NOT_FOUND) {
      mainWindow->setDescription(QString("I loaded %1 %2 into my %3.")
                                     .arg(getArticle(payloadName),
                                          payloadName.toLower(),
                                          target.toLower()));
      inventoryObj.removeItem(playerObj.getInventory(), payloadIndex);
      inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .setEffect(100);
    } else {
      mainWindow->setDescription(
          QString("I needed %1 %2.")
              .arg(getArticle(payloadName), payloadName.toLower()));
    }
  } else {
    missingItemMsg(mainWindow, getArticle(target) + " " + target);
  }
}

#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"

void Handling::examine(MainWindow *mainWindow, QString target) {
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (itemIndex != ITEM_NOT_FOUND) {
    QString description =
        inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
            .getDescription();
    mainWindow->setDescription(description);
  } else {
    missingItemMsg(mainWindow, getArticle(target) + " " + target);
  }
}

#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::examine(MainWindow *mainWindow, QString target) {
  int targetIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (targetIndex != -1) {
    QString description =
        inventoryObj.getInventoryItem(playerObj.getInventory(), targetIndex)
            .getDescription();
    mainWindow->setDescription(description);
  } else {
    missingItemMsg(mainWindow, getArticle(target) + " " + target);
  }
}

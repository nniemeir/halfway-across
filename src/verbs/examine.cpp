#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::examine(MainWindow *mainWindow, QString target) {
  int targetIndex = inventoryObj.searchInventory(player.getInventory(), target);
  if (targetIndex != -1) {
    QString description =
        inventoryObj.getInventoryItem(player.getInventory(), targetIndex)
            .getDescription();
    mainWindow->setDescription(description);
  } else {
    missingItemMsg(mainWindow, getArticle(target) + " " + target);
  }
}

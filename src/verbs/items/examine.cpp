#include "core/handling/inputhandler.h"
#include "core/handling/msghandler.h"
#include "core/handling/verbhandler.h"
#include "entities/player.h"

void VerbHandler::examine(MainWindow *mainWindow, QString target) {
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (itemIndex == ITEM_NOT_FOUND) {
    mainWindow->setDescription(msgHandlerObj.missingItem(
        inputHandlerObj.getArticle(target) + " " + target));
    return;
  }
  QString description =
      inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .getDescription();
  mainWindow->setDescription(description);
}

#include "../../../include/core/handling/inputhandler.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"

void VerbHandler::examine(MainWindow *mainWindow, QString target) {
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (itemIndex == ITEM_NOT_FOUND) {
    msgHandlerObj.missingItemMsg(mainWindow, inputHandlerObj.getArticle(target) + " " + target);
    return;
  }
  QString description =
      inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .getDescription();
  mainWindow->setDescription(description);
}

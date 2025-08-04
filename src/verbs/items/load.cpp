#include "core/handling/inputhandler.h"
#include "core/handling/msghandler.h"
#include "core/handling/verbhandler.h"
#include "entities/player.h"

void VerbHandler::load(MainWindow *mainWindow, QString target) {
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (itemIndex == ITEM_NOT_FOUND) {
    msgHandlerObj.missingItem(inputHandlerObj.getArticle(target) + " " +
                              target);
    return;
  }

  QString payloadName =
      inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .getPayload();
  int payloadIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), payloadName);
  if (payloadIndex == ITEM_NOT_FOUND) {
    mainWindow->setDescription(QString("I needed %1 %2.")
                                   .arg(inputHandlerObj.getArticle(payloadName),
                                        payloadName.toLower()));
    return;
  }

  inventoryObj.removeItem(playerObj.getInventory(), payloadIndex);
  inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
      .setEffect(100);

  mainWindow->setDescription(QString("I loaded %1 %2 into my %3.")
                                 .arg(inputHandlerObj.getArticle(payloadName),
                                      payloadName.toLower(), target.toLower()));
}

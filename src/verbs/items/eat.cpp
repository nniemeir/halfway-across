#include "../../../include/core/audio.h"
#include "../../../include/core/handling/inputhandler.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"

void VerbHandler::eat(MainWindow *mainWindow, QString target) {
  int itemIndex = inventoryObj.searchInventory(playerObj.getInventory(),
                                               "COOKED " + target);
  if (itemIndex == ITEM_NOT_FOUND) {
    itemIndex = inventoryObj.searchInventory(playerObj.getInventory(), target);
  }
  if (itemIndex == ITEM_NOT_FOUND) {
    msgHandlerObj.missingItemMsg(mainWindow, "any " + target);
    return;
  }
  if (inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .getType() != "FOOD") {
    mainWindow->setDescription(
        QString("It didn't seem wise to eat %1 %2.")
            .arg(inputHandlerObj.getArticle(target), target.toLower()));
    return;
  }
  if (playerObj.getHunger() == 100) {
    mainWindow->setDescription("I wasn't hungry at the time.");
    return;
  }
  sfxPlayer.play("qrc:/audio/sfx/eat.mp3", sfxPlayer.getdefSfxVol(), false);
  QString itemName =
      inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .getName();
  mainWindow->setDescription(QString("I ate some %1.").arg(itemName.toLower()));
  playerObj.setHunger(
      playerObj.getHunger() +
      inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .getEffect());
  inventoryObj.removeItem(playerObj.getInventory(), itemIndex);
}

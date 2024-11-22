#include "../../../include/core/audio.h"
#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"

void Handling::eat(MainWindow *mainWindow, QString target) {
  int itemIndex = inventoryObj.searchInventory(playerObj.getInventory(),
                                               "COOKED " + target);
  if (itemIndex == ITEM_NOT_FOUND) {
    itemIndex = inventoryObj.searchInventory(playerObj.getInventory(), target);
  }
  if (itemIndex != ITEM_NOT_FOUND) {
    if (inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
            .getType() == "FOOD") {
      if (playerObj.getHunger() < 100) {
        sfxPlayer.play("qrc:/audio/sfx/eat.mp3", sfxPlayer.getdefSfxVol(),
                       false);
        QString itemName =
            inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
                .getName();
        mainWindow->setDescription(
            QString("I ate some %1.").arg(itemName.toLower()));
        playerObj.setHunger(
            playerObj.getHunger() +
            inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
                .getEffect());
        inventoryObj.removeItem(playerObj.getInventory(), itemIndex);
      } else {
        mainWindow->setDescription("I wasn't hungry at the time.");
      }
    } else {
      mainWindow->setDescription(
          QString("It didn't seem wise to eat %1 %2.")
              .arg(handlingObj.getArticle(target), target.toLower()));
    }
  } else {
    missingItemMsg(mainWindow, "any " + target);
  }
}

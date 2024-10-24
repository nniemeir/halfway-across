#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::eat(MainWindow *mainWindow, QString target) {
  int targetIndex = inventoryObj.searchInventory(playerObj.getInventory(),
                                                 "COOKED " + target);
  if (targetIndex == -1) {
    targetIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), target);
  }
  if (targetIndex != -1) {
    if (inventoryObj.getInventoryItem(playerObj.getInventory(), targetIndex)
            .getType() == "FOOD") {
      if (playerObj.getHunger() < 100) {
        sfxPlayer.play("qrc:/audio/sfx/eat.mp3", sfxPlayer.getdefSfxVol(), 0);
        QString itemName =
            inventoryObj.getInventoryItem(playerObj.getInventory(), targetIndex)
                .getName();
        mainWindow->setDescription(
            QString("I ate some %1.").arg(itemName.toLower()));
        playerObj.setHunger(
            playerObj.getHunger() +
            inventoryObj.getInventoryItem(playerObj.getInventory(), targetIndex)
                .getEffect());
        inventoryObj.removeItem(playerObj.getInventory(), targetIndex);
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

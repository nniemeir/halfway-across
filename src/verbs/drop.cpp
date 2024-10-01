#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/locations.h"
#include "../../include/player.h"

void Handling::drop(MainWindow *mainWindow, QString target,
                    Location *location) {
  int targetIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (targetIndex != -1) {
    sfxPlayer.play("qrc:/audio/sfx/drop.mp3", sfxPlayer.getdefSfxVol(), 0);
    QString itemName =
        inventoryObj.getInventoryItem(playerObj.getInventory(), targetIndex)
            .getName();
    mainWindow->setDescription(
        QString("I dropped %1 %2.")
            .arg(getArticle(target), itemName.toLower()));
    int locationItemIndex =
        inventoryObj.searchInventory(location->getInventory(), target);
    inventoryObj.addItem(
        location->getInventory(),
        playerObj.getInventoryItem(playerObj.getInventory(), targetIndex),
        locationItemIndex);
    inventoryObj.removeItem(playerObj.getInventory(), targetIndex);
  } else {
    missingItemMsg(mainWindow, getArticle(target) + " " + target);
  }
}

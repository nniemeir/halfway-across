#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/locations.h"
#include "../../include/player.h"

void Handling::drop(MainWindow *mainWindow, QString target,
                    Location *location) {
  int targetIndex = inventoryObj.searchInventory(player.getInventory(), target);
  if (targetIndex != -1) {
    sfxPlayer.play("qrc:/audio/sfx/drop.mp3", sfxPlayer.getdefSfxVol(), 0);
    QString itemName =
        inventoryObj.getInventoryItem(player.getInventory(), targetIndex)
            .getName();
    mainWindow->setDescription(
        QString("I dropped %1 %2.").arg(getArticle(target)).arg(itemName));
    int locationItemIndex =
        inventoryObj.searchInventory(location->getInventory(), target);
    inventoryObj.addItem(
        location->getInventory(),
        player.getInventoryItem(player.getInventory(), targetIndex),
        locationItemIndex);
    inventoryObj.removeItem(player.getInventory(), targetIndex);
  } else {
    missingItemMsg(mainWindow, getArticle(target) + " " + target);
  }
}

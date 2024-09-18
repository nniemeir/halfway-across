#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/locations.h"
#include "../../include/player.h"

void Handling::drop(MainWindow *mainWindow, QString target,
                    Location *location) {
  int itemIndex = inventoryObj.searchInventory(player.getInventory(), target);
  if (itemIndex != -1) {
    sfxPlayer.play("qrc:/audio/sfx/drop.mp3", sfxPlayer.getdefSfxVol(), 0);
      QString itemName = inventoryObj.getInventoryItem(player.getInventory(), itemIndex).getName();
    mainWindow->setDescription(
        QString("I dropped %1 %2.")
            .arg(getArticle(target)).arg(itemName));
    int locationItemIndex =
        inventoryObj.searchInventory(location->getInventory(), target);
    inventoryObj.addItem(
        location->getInventory(),
        player.getInventoryItem(player.getInventory(), itemIndex),
        locationItemIndex);
    inventoryObj.removeItem(player.getInventory(), itemIndex);
  } else {
      mainWindow->setDescription(QString("I didn't have %1 %2 to drop.").arg(handle.getArticle(target)).arg(target.toLower()));
  }
}

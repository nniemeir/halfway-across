#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/locations.h"
#include "../../include/player.h"

void Handling::drop(MainWindow *mainWindow, QString target,
                    Location *location) {
  int itemIndex = inventoryObj.searchInventory(player.getInventory(), target);
  if (itemIndex != -1) {
    sfxPlayer.play("qrc:/audio/sfx/drop.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setDescription(
        QString("I dropped %1.")
            .arg(inventoryObj.getItemName(player.getInventory(), itemIndex)));
    int locationItemIndex =
        inventoryObj.searchInventory(location->getInventory(), target);
    inventoryObj.addItem(
        location->getInventory(),
        player.getInventoryItem(player.getInventory(), itemIndex),
        locationItemIndex);
    inventoryObj.removeItem(player.getInventory(), itemIndex);
  } else {
    mainWindow->setDescription("I didn't have that.");
  }
}

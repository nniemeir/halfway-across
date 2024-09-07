#include "../../include/handling.h"
#include "../../include/locations.h"
#include "../../include/player.h"
#include "../../include/audio.h"

void handling::drop(MainWindow *mainWindow, QString target,
                    Location *location) {
  int itemIndex = player.searchInventory(target);
  if (itemIndex != -1) {
    sfxPlayer.play("qrc:/audio/sfx/drop.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setDescription(
        QString("Dropped %1.").arg(player.getItemName(itemIndex)));
    int locationItemIndex = location->searchInventory(target);
    location->addItem(player.getInventoryItem(itemIndex), locationItemIndex);
    player.removeItem(itemIndex);
  } else {
    mainWindow->setDescription("You don't have that.");
  }
}

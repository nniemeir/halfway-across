#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"

void handling::take(MainWindow *mainWindow, QString target,
                    Location *location) {
  int itemIndex = location->searchInventory(target);
  if (itemIndex != -1) {
    sfxPlayer.play("qrc:/audio/sfx/take.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setDescription(
        QString("Took %1.").arg(location->getItemName(itemIndex).toLower()));
    int playerItemIndex = player.searchInventory(target);
      player.addItem(location->getInventoryItem(itemIndex), playerItemIndex);
      location->removeItem(itemIndex);
  } else {
      mainWindow->setDescription(QString("There is no %1 here.").arg(target.toLower()));
  }
}

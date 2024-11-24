#include "../../../include/core/audio.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"
#include "../../../include/survival/hunting.h"

void VerbHandler::skin(MainWindow *mainWindow, QString target,
                       Location *location) {
  int animalIndex =
      inventoryObj.searchInventory(location->getInventory(), target);
  int knifeIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "HUNTING KNIFE");
  if (knifeIndex == ITEM_NOT_FOUND) {
    mainWindow->setDescription("I needed a hunting knife to skin an animal.");
    return;
  }
  if (animalIndex == ITEM_NOT_FOUND) {
    mainWindow->setDescription(
        QString("There wasn't a slain %1 in the area for me to skin.")
            .arg(target.toLower()));
    return;
  }
  sfxPlayer.play("qrc:/audio/sfx/skin.mp3", sfxPlayer.getdefSfxVol(), 0);
  if (huntingObj.skinCarcass(target, location)) {
    mainWindow->setDescription(
        QString("I skinned the %1.").arg(target.toLower()));
    inventoryObj.removeItem(location->getInventory(), animalIndex);
    return;
  }
  mainWindow->setDescription(
      QString("I didn't have enough space to hold everything I harvested "
              "from the %1, so I left it on the ground.")
          .arg(target.toLower()));
  inventoryObj.removeItem(location->getInventory(), animalIndex);
}

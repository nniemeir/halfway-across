#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/hunting.h"
#include "../../include/player.h"

void Handling::skin(MainWindow *mainWindow, QString target,
                    Location *location) {
  int animalIndex =
      inventoryObj.searchInventory(location->getInventory(), target);
  int knifeIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "HUNTING KNIFE");
  if (knifeIndex != ITEM_NOT_FOUND) {
    if (animalIndex != ITEM_NOT_FOUND) {
      sfxPlayer.play("qrc:/audio/sfx/skin.mp3", sfxPlayer.getdefSfxVol(), 0);
      if (huntingObj.skinAnimal(target, location)) {
        mainWindow->setDescription(
            QString("I skinned the %1.").arg(target.toLower()));
      } else {
        mainWindow->setDescription(
            QString("I didn't have enough space to hold everything I harvested "
                    "from the %1, so I left it on the ground.")
                .arg(target.toLower()));
      }
      inventoryObj.removeItem(location->getInventory(), animalIndex);
    } else {
      mainWindow->setDescription(
          QString("There wasn't a slain %1 in the area for me to skin.")
              .arg(target.toLower()));
    }
  } else {
    mainWindow->setDescription("I needed a hunting knife to skin an animal.");
  }
}

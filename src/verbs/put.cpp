#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/locations.h"
#include "../../include/player.h"

void Handling::put(MainWindow *mainWindow, QString target, QString subject,
                   Location *location) {
  QMap<QString, std::vector<Item>> inventories = {
      {"GROUND", location->getInventory()}};

  if (inventories.contains(subject)) {
    std::vector<Item> destinationInv = inventories.value(subject);
    int targetIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), target);
    if (targetIndex != -1) {
      sfxPlayer.play("qrc:/audio/sfx/drop.mp3", sfxPlayer.getdefSfxVol(), 0);
      mainWindow->setDescription(QString("I put the %1 on the %2.")
                                     .arg(target.toLower(), subject.toLower()));
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
  } else {
    mainWindow->setDescription(
        QString("I couldn't put something on the %1.").arg(subject.toLower()));
  }
}

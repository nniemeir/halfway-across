#include "../../../include/core/audio.h"
#include "../../../include/core/handling.h"
#include "../../../include/entities/locations.h"
#include "../../../include/entities/player.h"

void Handling::put(MainWindow *mainWindow, QString target, QString subject,
                   Location *location) {
  QMap<QString, std::vector<Item>> inventories = {
      {"GROUND", location->getInventory()}};

  if (inventories.contains(subject)) {
    std::vector<Item> destinationInv = inventories.value(subject);
    int itemIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), target);
    if (itemIndex != ITEM_NOT_FOUND) {
      sfxPlayer.play("qrc:/audio/sfx/drop.mp3", sfxPlayer.getdefSfxVol(), 0);
      mainWindow->setDescription(QString("I put the %1 on the %2.")
                                     .arg(target.toLower(), subject.toLower()));
      int locationItemIndex =
          inventoryObj.searchInventory(location->getInventory(), target);
      inventoryObj.addItem(
          location->getInventory(),
          playerObj.getInventoryItem(playerObj.getInventory(), itemIndex),
          locationItemIndex);
      inventoryObj.removeItem(playerObj.getInventory(), itemIndex);
    } else {
      missingItemMsg(mainWindow, getArticle(target) + " " + target);
    }
  } else {
    mainWindow->setDescription(
        QString("I couldn't put something on the %1.").arg(subject.toLower()));
  }
}

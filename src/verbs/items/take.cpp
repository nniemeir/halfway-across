#include "../../../include/core/audio.h"
#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"
#include "../../../include/items/inventory.h"

void Handling::take(MainWindow *mainWindow, QString target,
                    Location *location) {
  int itemIndex =
      inventoryObj.searchInventory(location->getInventory(), target);
  if (itemIndex != ITEM_NOT_FOUND) {
    QString itemName =
        inventoryObj.getInventoryItem(location->getInventory(), itemIndex)
            .getName()
            .toLower();
    mainWindow->setDescription(
        QString("I took %1 %2.")
            .arg(handlingObj.getArticle(itemName), itemName));
    int playerItemIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), target);
    Item toAdd =
        inventoryObj.getInventoryItem(location->getInventory(), itemIndex);
    if (inventoryObj.fitsInventory(playerObj.getInventory(), toAdd)) {
      sfxPlayer.play("qrc:/audio/sfx/take.mp3", sfxPlayer.getdefSfxVol(), 0);
      inventoryObj.addItem(
          playerObj.getInventory(),
          inventoryObj.getInventoryItem(location->getInventory(), itemIndex),
          playerItemIndex);
      inventoryObj.removeItem(location->getInventory(), itemIndex);
    } else {
      mainWindow->setDescription(
          QString("I didn't have enough space to take %1 %2 with me.")
              .arg(handlingObj.getArticle(target), target.toLower()));
    }
  } else {
    mainWindow->setDescription(
        QString("There wasn't %1 %2 there.")
            .arg(handlingObj.getArticle(target), target.toLower()));
  }
}
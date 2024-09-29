#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/inventory.h"
#include "../../include/player.h"

void Handling::take(MainWindow *mainWindow, QString target,
                    Location *location)
{
  int itemIndex =
      inventoryObj.searchInventory(location->getInventory(), target);
  if (itemIndex != -1)
  {
    sfxPlayer.play("qrc:/audio/sfx/take.mp3", sfxPlayer.getdefSfxVol(), 0);
    QString itemName =
        inventoryObj.getInventoryItem(location->getInventory(), itemIndex)
            .getName()
            .toLower();
    mainWindow->setDescription(QString("I took %1 %2.")
                                   .arg(handle.getArticle(itemName))
                                   .arg(itemName));
    int playerItemIndex =
        inventoryObj.searchInventory(player.getInventory(), target);
    inventoryObj.addItem(
        player.getInventory(),
        inventoryObj.getInventoryItem(location->getInventory(), itemIndex),
        playerItemIndex);
    inventoryObj.removeItem(location->getInventory(), itemIndex);
  }
  else
  {
    mainWindow->setDescription(QString("There wasn't %1 %2 there.")
                                   .arg(handle.getArticle(target))
                                   .arg(target.toLower()));
  }
}

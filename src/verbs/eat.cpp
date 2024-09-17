#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::eat(MainWindow *mainWindow, QString target) {
  int itemIndex = inventoryObj.searchInventory(player.getInventory(), target);
  if (itemIndex != -1) {
    if (inventoryObj.getItemType(player.getInventory(), itemIndex) == "FOOD") {
      sfxPlayer.play("qrc:/audio/sfx/eat.mp3", sfxPlayer.getdefSfxVol(), 0);
      QString itemName = inventoryObj.getItemName(player.getInventory(), itemIndex).toLower();
      mainWindow->setDescription(
          QString("I ate %1 %2.").arg(getArticle(itemName)).arg(itemName));
      player.setHunger(
          player.getHunger() +
          inventoryObj.getItemEffect(player.getInventory(), itemIndex));
      inventoryObj.removeItem(player.getInventory(), itemIndex);
    } else {
      mainWindow->setDescription(QString("It didn't seem wise to eat %1 %2.").arg(handle.getArticle(target)).arg(target.toLower()));
    }
  } else {
    mainWindow->setDescription(
        QString("I didn't have %1 %2 to eat.").arg(getArticle(target)).arg(target.toLower()));
  }
}

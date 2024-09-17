#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"

// This will be greatly expanded upon in later versions
void Handling::craft(MainWindow *mainWindow, QString target) {
  if (target == "CANDLE") {
    int ingredient1Index =
        inventoryObj.searchInventory(player.getInventory(), "RENDERED FAT");
    int ingredient2Index =
        inventoryObj.searchInventory(player.getInventory(), "PIECE OF WOOD");
    if (ingredient1Index != -1 && ingredient1Index != -1) {
      sfxPlayer.play("qrc:/audio/sfx/craft.mp3", sfxPlayer.getdefSfxVol(), 0);
      mainWindow->setDescription(QString("I crafted %1 %2.").arg(handle.getArticle(target)).arg(target.toLower()));
      int resultIndex = inventoryObj.searchInventory(player.getInventory(),
                                                     "TALLOW CANDLE");
      inventoryObj.addItem(
          player.getInventory(),
          {"TALLOW CANDLE", 1, 1, 10, "ANIMAL FAT", "NONE"}, resultIndex);
      inventoryObj.removeItem(player.getInventory(), ingredient1Index);
      inventoryObj.removeItem(player.getInventory(), ingredient2Index);
    } else {
      mainWindow->setDescription(
          QString("I didn't have the resources to make %1 %2.").arg(getArticle(target)).arg(target));
    }
  } else {
    mainWindow->setDescription(
        QString("I didn't know how to make %1 %2.").arg(getArticle(target)).arg(target));
  }
}

#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"

// Hunting will be greatly expanded upon in later versions
void Handling::hunt(MainWindow *mainWindow, QString target,
                    Location *location) {
  if (location->getName() == "valley") {
    int bowIndex = inventoryObj.searchInventory(player.getInventory(), "BOW");
    int arrowIndex =
        inventoryObj.searchInventory(player.getInventory(), "ARROW");
    if (bowIndex != -1 && arrowIndex != -1) {
      if (target == "DEER") {
        sfxPlayer.play("qrc:/audio/sfx/arrow.mp3", sfxPlayer.getdefSfxVol(), 0);
        inventoryObj.removeItem(player.getInventory(), arrowIndex);
        mainWindow->setDescription(
            "I managed to drop a deer in a single shot.");
        int fatIndex =
            inventoryObj.searchInventory(player.getInventory(), "DEER FAT");
        inventoryObj.addItem(player.getInventory(),
                             {"DEER FAT", 1, 1, 10, "FAT", "NONE",
                              "I could cook it to get rendered fat."},
                             fatIndex);
        int meatIndex =
            inventoryObj.searchInventory(player.getInventory(), "DEER MEAT");
        inventoryObj.addItem(player.getInventory(),
                             {"DEER MEAT", 1, 1, 10, "RAW MEAT", "NONE",
                              "I could cook it to ease my hunger."},
                             meatIndex);
        int peltIndex =
            inventoryObj.searchInventory(player.getInventory(), "DEER PELT");
        inventoryObj.addItem(player.getInventory(),
                             {"DEER PELT", 1, 1, 10, "PELT", "NONE",
                              "I could use it for crafting."},
                             peltIndex);
      } else {
        mainWindow->setDescription(
            QString("I was unable to find any %1 in the valley.")
                .arg(target.toLower()));
      }
    } else {
      mainWindow->setDescription("I needed a weapon to hunt.");
    }
  } else {
    mainWindow->setDescription("It didn't seem like a good place to hunt.");
  }
}

#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::fill(MainWindow *mainWindow, QString target,
                    Location *location) {
  int canteenIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "CANTEEN");
  if (location->getName() == "The lake") {
    if (canteenIndex != -1) {
      if (worldObj.getChiseledIce() == 1) {
        if (inventoryObj
                .getInventoryItem(playerObj.getInventory(), canteenIndex)
                .getEffect() != 100) {
          sfxPlayer.play("qrc:/audio/sfx/lakeSplash.mp3", sfxPlayer.getdefSfxVol(), 0);
          mainWindow->setDescription("I filled my canteen with water.");
          inventoryObj.getInventoryItem(playerObj.getInventory(), canteenIndex)
              .setEffect(100);
        } else {
          mainWindow->setDescription("My canteen was already full.");
        }
      } else {
        mainWindow->setDescription(
            "I needed to be near exposed water to fill my canteen.");
      }
    } else {

      mainWindow->setDescription("I needed my canteen to gather water.");
    }
  } else {
    mainWindow->setDescription(
        "I needed to be near exposed water to fill my canteen.");
  }
}

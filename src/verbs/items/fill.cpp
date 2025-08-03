#include "core/handling/verbhandler.h"
#include "core/world.h"
#include "entities/player.h"

void VerbHandler::fill(MainWindow *mainWindow, QString target,
                       Location *location) {
  int canteenIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "CANTEEN");
  if (location->getName() != "The lake") {
    mainWindow->setDescription(
        "I needed to be near exposed water to fill my canteen.");
    return;
  }
  if (canteenIndex == ITEM_NOT_FOUND) {
    mainWindow->setDescription("I needed my canteen to gather water.");
    return;
  }
  if (worldObj.getChiseledIce()) {
    mainWindow->setDescription("The lake was frozen over.");
    return;
  }
  if (inventoryObj.getInventoryItem(playerObj.getInventory(), canteenIndex)
          .getEffect() == 100) {
    mainWindow->setDescription("My canteen was already full.");
  }
  mainWindow->playSfx("qrc:/audio/sfx/lakeSplash.mp3");
  mainWindow->setDescription("I filled my canteen with water.");
  inventoryObj.getInventoryItem(playerObj.getInventory(), canteenIndex)
      .setEffect(100);
}

#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::wait(MainWindow *mainWindow, Location *location) {

  QMap<QString, std::function<void()>> waitLocations;
  waitLocations["lake"] = [mainWindow, this]() { waitLake(mainWindow); };

  if (waitLocations.contains(location->getName())) {
    waitLocations[location->getName()]();
  } else {
    mainWindow->setDescription("I didn't feel safe waiting there.");
  }
}

void Handling::waitLake(MainWindow *mainWindow) {
  if (world.getLineSet() == 1) {
    QString generatedFish = world.generateFish();
    int itemIndex =
        inventoryObj.searchInventory(world.getFishInventory(), generatedFish);
    if (itemIndex != -1) {
      sfxPlayer.play("qrc:/audio/sfx/fishReel.mp3", sfxPlayer.getdefSfxVol(),
                     0);
      mainWindow->setDescription(
          QString("I caught a %1!\n")
              .arg(inventoryObj
                       .getInventoryItem(world.getFishInventory(), itemIndex)
                       .getName()
                       .toLower()));
      int playerItemIndex =
          inventoryObj.searchInventory(player.getInventory(), generatedFish);
      inventoryObj.addItem(
          player.getInventory(),
          inventoryObj.getInventoryItem(world.getFishInventory(), itemIndex),
          playerItemIndex);
    }
    world.setLineSet(0);
  } else {
    mainWindow->setDescription("I waited a while.");
  }
}

#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void handling::wait(MainWindow *mainWindow, Location *location) {
  if (location->getName() == "lake") {
    waitLake(mainWindow);
  } else {
    mainWindow->setDescription("You can't do that here.");
  }
}

void handling::waitLake(MainWindow *mainWindow) {
  if (world.getLineSet() == 1) {
    QString generatedFish = world.generateFish();
    int itemIndex = world.searchFish(generatedFish);
    if (itemIndex != -1) {
      sfxPlayer.play("qrc:/audio/sfx/fishReel.mp3", sfxPlayer.getdefSfxVol(), 0);
      mainWindow->setDescription(
          QString("You caught a %1!\n")
              .arg(world.getFishName(itemIndex).toLower()));
      int playerItemIndex = player.searchInventory(generatedFish);
        player.addItem(world.getFish(itemIndex), playerItemIndex);
    }
    world.setLineSet(0);
  }
}

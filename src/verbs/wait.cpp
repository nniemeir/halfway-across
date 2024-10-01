#include "../../include/audio.h"
#include "../../include/fishing.h"
#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::wait(MainWindow *mainWindow, Location *location) {

  QMap<QString, std::function<void()>> waitLocations;
  waitLocations["The lake"] = [mainWindow, this]() { waitLake(mainWindow); };

  if (waitLocations.contains(location->getName())) {
    waitLocations[location->getName()]();
  } else {
    notAllowedInLocMsg(mainWindow, "wait safely");
  }
}

void Handling::waitLake(MainWindow *mainWindow) {
  int rodIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "FISHING ROD");
  if (rodIndex != -1) {
    Item rod =
        inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex);
    if (rod.getActive() == 1) {
      sfxPlayer.play("qrc:/audio/sfx/fishReel.mp3", sfxPlayer.getdefSfxVol(),
                     0);
      inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
          .setActive(0);
      mainWindow->setDescription(fishingObj.activity(rodIndex));
    }
  } else {
    waitMsg(mainWindow);
  }
}

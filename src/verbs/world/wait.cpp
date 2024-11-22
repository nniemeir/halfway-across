#include "../../../include/core/audio.h"
#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"
#include "../../../include/survival/fishing.h"

void Handling::wait(MainWindow *mainWindow, Location *location) {
  QMap<QString, std::function<void()>> waitLocations{
      {"The lake", [mainWindow, this]() { waitLake(mainWindow); }}};
  if (waitLocations.contains(location->getName())) {
    waitLocations[location->getName()]();
  } else {
    notAllowedInLocMsg(mainWindow, "wait safely");
  }
}

void Handling::waitLake(MainWindow *mainWindow) {
  int rodIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "FISHING ROD");
  if (rodIndex != ITEM_NOT_FOUND) {
    if (fishingObj.getDailyFished() < 2) {
      Item rod =
          inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex);
      if (rod.getActive()) {
        sfxPlayer.play("qrc:/audio/sfx/fishReel.mp3", sfxPlayer.getdefSfxVol(),
                       0);
        inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
            .setActive(false);
        mainWindow->setDescription(fishingObj.activity(rodIndex));
      }
    } else {
      mainWindow->setDescription("I was too tired to fish anymore that day.");
    }
  } else {
    waitMsg(mainWindow);
  }
}

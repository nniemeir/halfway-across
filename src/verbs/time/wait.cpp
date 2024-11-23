#include "../../../include/core/audio.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"
#include "../../../include/survival/fishing.h"

void VerbHandler::wait(MainWindow *mainWindow, Location *location) {
  QMap<QString, std::function<void()>> waitLocations{
      {"The lake", [mainWindow, this]() { waitLake(mainWindow); }}};
  if (!waitLocations.contains(location->getName())) {
    msgHandlerObj.notAllowedInLocMsg(mainWindow, "wait safely");
    return;
  }
  waitLocations[location->getName()]();
}

void VerbHandler::waitLake(MainWindow *mainWindow) {
  int rodIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "FISHING ROD");

  if (!inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
           .getActive()) {
    msgHandlerObj.waitMsg(mainWindow);
    return;
  }
  if (fishingObj.getDailyFished() == 2) {
    mainWindow->setDescription("I was too tired to fish anymore that day.");
    return;
  }
  sfxPlayer.play("qrc:/audio/sfx/fishReel.mp3", sfxPlayer.getdefSfxVol(), 0);
  inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
      .setActive(false);
  mainWindow->setDescription(fishingObj.activity(rodIndex));
}

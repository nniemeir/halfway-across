#include "core/handling/msghandler.h"
#include "core/handling/verbhandler.h"
#include "entities/player.h"
#include "survival/fishing.h"

void VerbHandler::wait(MainWindow *mainWindow, Location *location) {
  QMap<QString, std::function<void()>> waitLocations{
      {"The lake", [mainWindow, this]() { waitLake(mainWindow); }}};
  if (!waitLocations.contains(location->getName())) {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("wait safely"));
    return;
  }
  waitLocations[location->getName()]();
}

void VerbHandler::waitLake(MainWindow *mainWindow) {
  int rodIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "FISHING ROD");
  if (inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
          .getActive()) {
    waitFishing(mainWindow, rodIndex);
    return;
  }
  mainWindow->setDescription(MsgHandler::WAIT);
  return;
}

void VerbHandler::waitFishing(MainWindow *mainWindow, int rodIndex) {
  if (fishingObj.getDailyAttempts() == 2) {
    mainWindow->setDescription("I was too tired to fish anymore that day.");
    return;
  }
  mainWindow->playSfx("qrc:/audio/sfx/fishReel.mp3");
  inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
      .setActive(false);
  mainWindow->setDescription(fishingObj.seek());
}

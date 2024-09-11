#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::wait(MainWindow *mainWindow, Location *location) {

    QMap<QString, std::function<void()>> actions;
    // actions["camp"] = [mainWindow, this]() {     waitCamp(mainWindow);};
    // actions["campPath"] = [mainWindow, this]() {     waitCampPath(mainWindow);};
    // actions["cave"] = [mainWindow, this]() {     waitCave(mainWindow);};
    // actions["caveEntrance"] = [mainWindow, this]() {     waitCaveEntrance(mainWindow);};
    actions["lake"] = [mainWindow, this]() {     waitLake(mainWindow);};
    // actions["valley"] = [mainWindow, this]() {     waitValley(mainWindow);};

    if (actions.contains(location->getName())) {
        actions[location->getName()]();
    } else {
        mainWindow->setDescription(QString("You can't do that here."));
    }
}


void Handling::waitLake(MainWindow *mainWindow) {
  if (world.getLineSet() == 1) {
    QString generatedFish = world.generateFish();
    int itemIndex = inventoryObj.searchInventory(world.getFishInventory(), generatedFish);
    if (itemIndex != -1) {
      sfxPlayer.play("qrc:/audio/sfx/fishReel.mp3", sfxPlayer.getdefSfxVol(), 0);
      mainWindow->setDescription(
          QString("You caught a %1!\n")
              .arg(inventoryObj.getItemName(world.getFishInventory(), itemIndex).toLower()));
      int playerItemIndex = inventoryObj.searchInventory(player.getInventory(), generatedFish);
        inventoryObj.addItem(player.getInventory(), inventoryObj.getInventoryItem(world.getFishInventory(), itemIndex), playerItemIndex);
    }
    world.setLineSet(0);
  }
}

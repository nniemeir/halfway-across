#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::use(MainWindow *mainWindow, QString target, Location *location) {

        QMap<QString, std::function<void()>> actions;
        // actions["camp"] = [mainWindow, target, this]() {     useCamp(mainWindow, target);};
        // actions["campPath"] = [mainWindow, target, this]() {     useCampPath(mainWindow, target);};
        // actions["cave"] = [mainWindow, target, this]() {     useCave(mainWindow, target);};
        // actions["caveEntrance"] = [mainWindow, target, this]() {     useCaveEntrance(mainWindow, target);};
        actions["lake"] = [mainWindow, target, this]() {     useLake(mainWindow, target);};
        // actions["valley"] = [mainWindow, target, this]() {     useValley(mainWindow, target);};

        if (actions.contains(location->getName())) {
            actions[location->getName()]();
        } else {
            mainWindow->setDescription(QString("You can't do that here."));
        }
}

void Handling::useLake(MainWindow *mainWindow, QString target) {
  if (target == "CHISEL") {
    if (inventoryObj.searchInventory(player.getInventory(), "CHISEL") != -1) {
      sfxPlayer.play("qrc:/audio/sfx/chiselLake.mp3", sfxPlayer.getdefSfxVol(), 0);
      mainWindow->setDescription("You chisel a hole in the ice.\n");
      world.setChiseledIce(1);
    } else {
      mainWindow->setDescription("You don't have a chisel.");
    }
  } else if (target == "FISHING ROD") {
    if (inventoryObj.searchInventory(player.getInventory(), "FISHING ROD") != -1) {
      if (world.getChiseledIce()) {
        sfxPlayer.play("qrc:/audio/sfx/fishSet.mp3", sfxPlayer.getdefSfxVol(), 0);
        world.setLineSet(1);
        mainWindow->setDescription(
            "You drop your line into the hole in the ice.\n");
      } else {
        mainWindow->setDescription(
            "You do not know where to use the fishing rod.\n");
      }
    } else {
      mainWindow->setDescription("You don't have a fishing rod\n");
    }
  }
}

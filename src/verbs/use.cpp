#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::use(MainWindow *mainWindow, QString target, Location *location) {

  QMap<QString, std::function<void()>> actions;
  // actions["camp"] = [mainWindow, target, this]() {     useCamp(mainWindow,
  // target);}; actions["campPath"] = [mainWindow, target, this]() {
  // useCampPath(mainWindow, target);};
  actions["cave"] = [mainWindow, target, this]() {
    useCave(mainWindow, target);
  };
  // actions["caveEntrance"] = [mainWindow, target, this]() {
  // useCaveEntrance(mainWindow, target);};
  actions["lake"] = [mainWindow, target, this]() {
    useLake(mainWindow, target);
  };
  // actions["valley"] = [mainWindow, target, this]() { useValley(mainWindow,
  // target);};

  if (actions.contains(location->getName())) {
    actions[location->getName()]();
  } else {
    mainWindow->setDescription(QString("I couldn't do that there."));
  }
}

void Handling::useCave(MainWindow *mainWindow, QString target) {
  if (target == "LANTERN") {
    if (inventoryObj.searchInventory(player.getInventory(), "LANTERN") != -1) {
      sfxPlayer.play("qrc:/audio/sfx/lanternRustle.mp3",
                     sfxPlayer.getdefSfxVol(), 0);
      mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                              &caveLit);
    } else {
      mainWindow->setDescription("I didn't have a lantern.");
    }
  }
}

void Handling::useLake(MainWindow *mainWindow, QString target) {
  if (target == "CHISEL") {
    if (inventoryObj.searchInventory(player.getInventory(), "CHISEL") != -1) {
      sfxPlayer.play("qrc:/audio/sfx/chiselLake.mp3", sfxPlayer.getdefSfxVol(),
                     0);
      mainWindow->setDescription("I chiseled a hole in the ice.\n");
      world.setChiseledIce(1);
    } else {
      mainWindow->setDescription("I didn't have a chisel.");
    }
  } else if (target == "FISHING ROD") {
    int rodIndex =
        inventoryObj.searchInventory(player.getInventory(), "FISHING ROD");
    if (rodIndex != -1) {
      if (world.getChiseledIce()) {
        if (inventoryObj.getItemEffect(player.getInventory(), rodIndex) ==
            100) {
          inventoryObj.setItemEffect(player.getInventory(), rodIndex, 0);
          sfxPlayer.play("qrc:/audio/sfx/fishSet.mp3", sfxPlayer.getdefSfxVol(),
                         0);
          world.setLineSet(1);
          mainWindow->setDescription(
              "I dropped my line into the hole I had cut into the ice.\n");
        } else {
          mainWindow->setDescription("I needed to put some bait on the line if I expected to catch anything.\n");
        }
      } else {
        mainWindow->setDescription(
            "I didn't know where to use the fishing rod.\n");
      }
    }
  } else {
    mainWindow->setDescription("I didn't have a fishing rod\n");
  }
}

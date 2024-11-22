#include "../../../include/core/audio.h"
#include "../../../include/core/handling.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/player.h"

void Handling::use(MainWindow *mainWindow, QString target, Location *location) {

  QMap<QString, std::function<void()>> useLocations{
      {"The dark cave",
       [mainWindow, target, this]() { useCave(mainWindow, target); }},
      {"The lake",
       [mainWindow, target, this]() { useLake(mainWindow, target); }}};
  if (useLocations.contains(location->getName())) {
    useLocations[location->getName()]();
  } else {
    notAllowedInLocMsg(mainWindow, "use anything");
  }
}

void Handling::useCave(MainWindow *mainWindow, QString target) {
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "LANTERN");
  if (target == "LANTERN") {
    if (itemIndex != ITEM_NOT_FOUND) {
      if (inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
              .getEffect() == 100) {
        sfxPlayer.play("qrc:/audio/sfx/flint.mp3", sfxPlayer.getdefSfxVol(), 0);
        mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                                &caveLit);
      } else {
        mainWindow->setDescription("My lantern needs a fuel source.");
      }
    } else {
      mainWindow->setDescription("I didn't have a lantern.");
    }
  } else {
    notAllowedInLocMsg(
        mainWindow, QString("use %1 %2")
                        .arg(handlingObj.getArticle(target), target.toLower()));
  }
}

void Handling::useLake(MainWindow *mainWindow, QString target) {
  if (target == "CHISEL") {
    if (inventoryObj.searchInventory(playerObj.getInventory(), "CHISEL") !=
        ITEM_NOT_FOUND) {
      sfxPlayer.play("qrc:/audio/sfx/chiselLake.mp3", sfxPlayer.getdefSfxVol(),
                     0);
      mainWindow->setDescription("I chiseled a hole in the ice.\n");
      worldObj.setChiseledIce(true);
    } else {
      missingItemMsg(mainWindow, getArticle(target) + " " + target);
    }
  } else if (target == "FISHING ROD") {
    int rodIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), "FISHING ROD");
    if (rodIndex != ITEM_NOT_FOUND) {
      if (worldObj.getChiseledIce()) {
        if (inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
                .getEffect() == 100) {
          inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
              .setEffect(0);
          sfxPlayer.play("qrc:/audio/sfx/fishSet.mp3", sfxPlayer.getdefSfxVol(),
                         0);
          inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
              .setActive(true);
          mainWindow->setDescription(
              "I dropped my line into the hole I had cut into the ice.\n");
        } else {
          mainWindow->setDescription("I needed to put some bait on the line if "
                                     "I expected to catch anything.\n");
        }
      } else {
        mainWindow->setDescription(
            "I needed to be near an exposed body of water to fish.\n");
      }
    } else {
      missingItemMsg(mainWindow, getArticle(target) + " " + target);
    }
  } else {
    notAllowedInLocMsg(
        mainWindow, QString("use %1 %2")
                        .arg(handlingObj.getArticle(target), target.toLower()));
  }
}
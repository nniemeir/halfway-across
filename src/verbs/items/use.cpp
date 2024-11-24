#include "../../../include/core/audio.h"
#include "../../../include/core/handling/inputhandler.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/player.h"

void VerbHandler::use(MainWindow *mainWindow, QString target,
                      Location *location) {

  QMap<QString, std::function<void()>> useLocations{
      {"The dark cave",
       [mainWindow, target, this]() { useCave(mainWindow, target); }},
      {"The lake",
       [mainWindow, target, this]() { useLake(mainWindow, target); }}};
  if (useLocations.contains(location->getName())) {
    useLocations[location->getName()]();
    return;
  }
  mainWindow->setDescription(msgHandlerObj.invalidLocation("use anything"));
}

void VerbHandler::useCave(MainWindow *mainWindow, QString target) {
  if (target == "LANTERN") {
    int itemIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), "LANTERN");
    if (itemIndex == ITEM_NOT_FOUND) {
      mainWindow->setDescription("I didn't have a lantern.");
      return;
    }
    if (inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
            .getEffect() != 100) {
      mainWindow->setDescription("My lantern needs a fuel source.");
      return;
    }
    sfxPlayer.play("qrc:/audio/sfx/flint.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                            &caveLit);
    return;
  }
  mainWindow->setDescription(msgHandlerObj.invalidLocation(
      QString("use %1 %2")
          .arg(inputHandlerObj.getArticle(target), target.toLower())));
}

void VerbHandler::useLake(MainWindow *mainWindow, QString target) {
  if (target == "CHISEL") {
    if (inventoryObj.searchInventory(playerObj.getInventory(), "CHISEL") ==
        ITEM_NOT_FOUND) {
      mainWindow->setDescription(msgHandlerObj.missingItem(
          inputHandlerObj.getArticle(target) + " " + target));
      return;
    }
    sfxPlayer.play("qrc:/audio/sfx/chiselLake.mp3", sfxPlayer.getdefSfxVol(),
                   0);
    mainWindow->setDescription("I chiseled a hole in the ice.\n");
    worldObj.setChiseledIce(true);
    return;
  }
  if (target == "FISHING ROD") {
    int rodIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), "FISHING ROD");
    if (rodIndex == ITEM_NOT_FOUND) {
      mainWindow->setDescription(msgHandlerObj.missingItem(
          inputHandlerObj.getArticle(target) + " " + target));
      return;
    }
    if (!worldObj.getChiseledIce()) {
      mainWindow->setDescription("The lake had frozen over.\n");
      return;
    }
    if (inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
            .getActive()) {
      sfxPlayer.play("qrc:/audio/sfx/fishReel.mp3", sfxPlayer.getdefSfxVol(),
                     0),
          mainWindow->setDescription("I reeled in my line.");
      return;
    }
    if (inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
            .getEffect() != 100) {
      mainWindow->setDescription("I needed to put some bait on the line if "
                                 "I expected to catch anything.\n");
      return;
    }
    inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
        .setEffect(0);
    sfxPlayer.play("qrc:/audio/sfx/fishSet.mp3", sfxPlayer.getdefSfxVol(), 0);
    inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
        .setActive(true);
    mainWindow->setDescription(
        "I dropped my line into the hole I had cut into the ice.\n");
  }
  mainWindow->setDescription(msgHandlerObj.invalidLocation(
      QString("use %1 %2")
          .arg(inputHandlerObj.getArticle(target), target.toLower())));
}

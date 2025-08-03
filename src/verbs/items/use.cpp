#include "core/handling/inputhandler.h"
#include "core/handling/msghandler.h"
#include "core/handling/verbhandler.h"
#include "core/world.h"
#include "entities/player.h"

void VerbHandler::use(MainWindow *mainWindow, QString target,
                      Location *location) {
  QMap<QString, std::function<void()>> useCave{
      {{"LANTERN", [mainWindow, this]() { useLanternAtCave(mainWindow); }}}};
  QMap<QString, std::function<void()>> useLake{
      {{"CHISEL", [mainWindow, this]() { useChiselAtLake(mainWindow); }},
       {"FISHING ROD", [mainWindow, this]() { useRodAtLake(mainWindow); }}}};

  QMap<QString, QMap<QString, std::function<void()>>> useLocations{
      {"The dark cave", useCave}, {"The lake", useLake}};

  if (!useLocations.contains(location->getName())) {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("use anything"));
    return;
  }
  if (inventoryObj.searchInventory(playerObj.getInventory(), target) ==
      ITEM_NOT_FOUND) {
    mainWindow->setDescription(msgHandlerObj.missingItem(
        inputHandlerObj.getArticle(target) + " " + target));
    return;
  }
  if (useLocations[location->getName()].contains(target)) {
    useLocations[location->getName()][target]();
    return;
  }
  mainWindow->setDescription(msgHandlerObj.invalidLocation("use that"));
}

void VerbHandler::useLanternAtCave(MainWindow *mainWindow) {
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "LANTERN");
  if (inventoryObj.getInventoryItem(playerObj.getInventory(), itemIndex)
          .getEffect() != 100) {
    mainWindow->setDescription("My lantern needs a fuel source.");
    return;
  }
  mainWindow->playSfx("qrc:/audio/sfx/flint.mp3");
  mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                          &caveLit);
}

void VerbHandler::useRodAtLake(MainWindow *mainWindow) {
  int rodIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "FISHING ROD");
  if (!worldObj.getChiseledIce()) {
    mainWindow->setDescription("The lake had frozen over.\n");
    return;
  }
  if (inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
          .getActive()) {
    mainWindow->playSfx("qrc:/audio/sfx/fishReel.mp3");
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
  mainWindow->playSfx("qrc:/audio/sfx/fishSet.mp3");
  inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
      .setActive(true);
  mainWindow->setDescription(
      "I dropped my line into the hole I had cut into the ice.\n");
}

void VerbHandler::useChiselAtLake(MainWindow *mainWindow) {
  if (worldObj.getChiseledIce()) {
    return;
  }
  mainWindow->playSfx("qrc:/audio/sfx/chiselLake.mp3");
  mainWindow->setDescription("I chiseled a hole in the ice.\n");
  worldObj.setChiseledIce(true);
}

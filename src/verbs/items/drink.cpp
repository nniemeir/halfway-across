#include "../../../include/core/audio.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/player.h"

void VerbHandler::drink(MainWindow *mainWindow, QString target,
                     Location *location) {
  if (target == "CANTEEN") {
    drinkCanteen(mainWindow, target);
    return;
  }
  QMap<QString, std::function<void()>> drinkLocations{
      {"The lake",
       [mainWindow, target, this]() { drinkLake(mainWindow, target); }}};
  if (drinkLocations.contains(location->getName())) {
    drinkLocations[location->getName()]();
    return;
  }
  msgHandlerObj.notAllowedInLocMsg(mainWindow, "drink anything");
}

void VerbHandler::drinkLake(MainWindow *mainWindow, QString target) {
  if (target != "LAKE") {
    mainWindow->setDescription(
        QString("I couldn't drink from %1.").arg(target.toLower()));
    return;
  }
  if (!worldObj.getChiseledIce()) {
      mainWindow->setDescription("The lake was frozen over.");
      return;
  }
    if (playerObj.getThirst() == 100) {
        mainWindow->setDescription("I wasn't thirsty.");
        return;
    }
      sfxPlayer.play("qrc:/audio/sfx/lakeSplash.mp3", sfxPlayer.getdefSfxVol(),
                     false);
      mainWindow->setDescription(
          "I felt more refreshed after drinking some cold water.");
      playerObj.setThirst(playerObj.getThirst() + 20);
}

void VerbHandler::drinkCanteen(MainWindow *mainWindow, QString target) {
  if (playerObj.getThirst() == 100) {
    mainWindow->setDescription("I wasn't thirsty.");
    return;
  }
  int canteenIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "CANTEEN");
  if (canteenIndex == ITEM_NOT_FOUND) {
    mainWindow->setDescription("I didn't have my canteen.");
    return;
  }
  if (inventoryObj.getInventoryItem(playerObj.getInventory(), canteenIndex)
          .getEffect() == 0) {
    mainWindow->setDescription("My canteen was empty.");
    return;
  }
  sfxPlayer.play("qrc:/audio/sfx/drink.mp3", sfxPlayer.getdefSfxVol(), false);
  mainWindow->setDescription(
      "I quenched my thirst using the water in my canteen.");
  inventoryObj.getInventoryItem(playerObj.getInventory(), canteenIndex)
      .setEffect(
          inventoryObj.getInventoryItem(playerObj.getInventory(), canteenIndex)
              .getEffect() -
          50);
  playerObj.setThirst(100);
}

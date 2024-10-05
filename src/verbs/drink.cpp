#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::drink(MainWindow *mainWindow, QString target,
                     Location *location) {
  if (target == "CANTEEN") {
    drinkCanteen(mainWindow, target);
  } else {
    QMap<QString, std::function<void()>> drinkLocations;
    drinkLocations["The lake"] = [mainWindow, target, this]() {
      drinkLake(mainWindow, target);
    };

    if (drinkLocations.contains(location->getName())) {
      drinkLocations[location->getName()]();
    } else {
      notAllowedInLocMsg(mainWindow, "drink anything");
    }
  }
}

void Handling::drinkLake(MainWindow *mainWindow, QString target) {
  if (target == "LAKE") {
    if (worldObj.getChiseledIce() == 1) {
      if (playerObj.getThirst() < 100) {
        sfxPlayer.play("qrc:/audio/sfx/lakeSplash.mp3",
                       sfxPlayer.getdefSfxVol(), 0);
        mainWindow->setDescription(
            "I felt more refreshed after drinking some cold water.");
        playerObj.setThirst(playerObj.getThirst() + 20);
      } else {
        mainWindow->setDescription("I wasn't thirsty.");
      }
    } else {
      mainWindow->setDescription("The lake was frozen over.");
    }
  } else {
    mainWindow->setDescription(
        QString("I couldn't drink from %1.").arg(target.toLower()));
  }
}

void Handling::drinkCanteen(MainWindow *mainWindow, QString target) {
  if (playerObj.getThirst() != 100) {
    int canteenIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), "CANTEEN");
    if (canteenIndex != -1) {
      if (inventoryObj.getInventoryItem(playerObj.getInventory(), canteenIndex)
              .getEffect() != 0) {
        sfxPlayer.play("qrc:/audio/sfx/drink.mp3", sfxPlayer.getdefSfxVol(), 0);
        mainWindow->setDescription(
            "I quenched my thirst using the water in my canteen.");
        inventoryObj.getInventoryItem(playerObj.getInventory(), canteenIndex)
            .setEffect(
                inventoryObj
                    .getInventoryItem(playerObj.getInventory(), canteenIndex)
                    .getEffect() -
                50);
        playerObj.setThirst(100);
      } else {
        mainWindow->setDescription("My canteen was empty.");
      }
    } else {
      mainWindow->setDescription("I didn't have my canteen.");
    }
  } else {
    mainWindow->setDescription("I wasn't thirsty.");
  }
}

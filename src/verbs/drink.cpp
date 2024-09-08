#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void handling::drink(MainWindow *mainWindow, QString target,
                     Location *location) {
  if (location->getName() == "lake") {
    drinkLake(mainWindow, target);
  } else {
    mainWindow->setDescription("You can't do that here.");
  }
}

void handling::drinkLake(MainWindow *mainWindow, QString target) {
  if (target == "FROM LAKE") {
        if (world.getChiseledIce() == 1) {
    mainWindow->setDescription(
        "You feel more refreshed drinking the cold water");
    player.setThirst(player.getThirst() + 20);
        } else {
            mainWindow->setDescription(
                "The lake is frozen over.");
        }
  }
}

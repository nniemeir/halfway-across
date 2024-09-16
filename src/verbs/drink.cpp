#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::drink(MainWindow *mainWindow, QString target,
                     Location *location) {

  QMap<QString, std::function<void()>> actions;
  // actions["camp"] = [mainWindow, target, this]() {     drinkCamp(mainWindow,
  // target);}; actions["campPath"] = [mainWindow, target, this]() {
  // drinkCampPath(mainWindow, target);}; actions["cave"] = [mainWindow, target,
  // this]() {     drinkCave(mainWindow, target);}; actions["caveEntrance"] =
  // [mainWindow, target, this]() {     drinkCaveEntrance(mainWindow, target);};
  actions["lake"] = [mainWindow, target, this]() {
    drinkLake(mainWindow, target);
  };
  // actions["valley"] = [mainWindow, target, this]() { drinkValley(mainWindow,
  // target);};

  if (actions.contains(location->getName())) {
    actions[location->getName()]();
  } else {
    mainWindow->setDescription(QString("I couldn't do that here."));
  }
}

void Handling::drinkLake(MainWindow *mainWindow, QString target) {
  if (target == "FROM LAKE") {
    if (world.getChiseledIce() == 1) {
      mainWindow->setDescription(
          "I felt more refreshed after drinking the cold water.");
      player.setThirst(player.getThirst() + 20);
    } else {
      mainWindow->setDescription("The lake was frozen over.");
    }
  }
}

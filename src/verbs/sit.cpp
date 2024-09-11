#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::sit(MainWindow *mainWindow, QString target, Location *location) {

    QMap<QString, std::function<void()>> actions;
    actions["camp"] = [mainWindow, target, this]() {     sitCamp(mainWindow, target);};
    // actions["campPath"] = [mainWindow, target, this]() {     sitCampPath(mainWindow, target);};
    // actions["cave"] = [mainWindow, target, this]() {     sitCave(mainWindow, target);};
    // actions["caveEntrance"] = [mainWindow, target, this]() {     sitCaveEntrance(mainWindow, target);};
    // actions["lake"] = [mainWindow, target, this]() {     sitLake(mainWindow, target);};
    // actions["valley"] = [mainWindow, target, this]() {     sitValley(mainWindow, target);};

    if (actions.contains(location->getName())) {
        actions[location->getName()]();
    } else {
        mainWindow->setDescription(QString("You can't do that here."));
    }
}

void Handling::sitCamp(MainWindow *mainWindow, QString target) {
  if (target == "LOG") {
    mainWindow->setDescription("You feel a bit warmer sitting by the fire.");
    player.setStanding(0);
  }
  else if (target == "FIRE") {
      mainWindow->setDescription("You burned yourself.");
      player.setHealth(player.getHealth() - 20);
  } else {
    mainWindow->setDescription("You can't sit there.");
  }
}

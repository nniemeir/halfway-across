#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::sit(MainWindow *mainWindow, QString target, Location *location) {

  QMap<QString, std::function<void()>> sitLocations;
  sitLocations["camp"] = [mainWindow, target, this]() {
    sitCamp(mainWindow, target);
  };
  // sitLocations["campPath"] = [mainWindow, target, this]() {
  // sitCampPath(mainWindow, target);}; sitLocations["cave"] = [mainWindow, target,
  // this]() {     sitCave(mainWindow, target);}; sitLocations["caveEntrance"] =
  // [mainWindow, target, this]() {     sitCaveEntrance(mainWindow, target);};
  // sitLocations["lake"] = [mainWindow, target, this]() {     sitLake(mainWindow,
  // target);}; sitLocations["valley"] = [mainWindow, target, this]() {
  // sitValley(mainWindow, target);};

  if (sitLocations.contains(location->getName())) {
    sitLocations[location->getName()]();
  } else {
    mainWindow->setDescription(QString("I couldn't sit down on anything there."));
  }
}

void Handling::sitCamp(MainWindow *mainWindow, QString target) {
  if (target == "LOG") {
    mainWindow->setDescription("I felt a bit warmer sitting by the fire.");
    player.setStanding(0);
  } else if (target == "FIRE") {
    mainWindow->setDescription("I burned myself.");
    if (player.setHealth(player.getHealth() - 20)) {
      mainWindow->setLocation(camp.getMusicPath(), camp.getAmbiencePath(),
                              &perished);
    }
  } else {
    mainWindow->setDescription("I couldn't sit there.");
  }
}

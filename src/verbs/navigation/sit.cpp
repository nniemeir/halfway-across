#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"

void Handling::sit(MainWindow *mainWindow, QString target, Location *location) {
  QMap<QString, std::function<void()>> sitLocations{
      {"Camp", [mainWindow, target, this]() { sitCamp(mainWindow, target); }}};

  if (sitLocations.contains(location->getName())) {
    sitLocations[location->getName()]();
  } else {
    notAllowedInLocMsg(mainWindow, "sit on anything");
  }
}

void Handling::sitCamp(MainWindow *mainWindow, QString target) {
  if (target == "LOG") {
    mainWindow->setDescription("I felt a bit cozier sitting by the fire.");
    playerObj.setStanding(false);
  } else if (target == "FIRE") {
    mainWindow->setDescription("I burned myself.");
    if (!playerObj.setHealth(playerObj.getHealth() - 20)) {
      gameOverMsg(mainWindow, "HEALTH");
    }
  } else {
    mainWindow->setDescription("I couldn't sit there.");
  }
}

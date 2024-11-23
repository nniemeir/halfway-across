#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"

void VerbHandler::sit(MainWindow *mainWindow, QString target, Location *location) {
  QMap<QString, std::function<void()>> sitLocations{
      {"Camp", [mainWindow, target, this]() { sitCamp(mainWindow, target); }}};

  if (!sitLocations.contains(location->getName())) {
    msgHandlerObj.notAllowedInLocMsg(mainWindow, "sit on anything");
    return;
  }
  sitLocations[location->getName()]();
}

void VerbHandler::sitCamp(MainWindow *mainWindow, QString target) {
  if (target == "LOG") {
    mainWindow->setDescription("I felt a bit cozier sitting by the fire.");
    playerObj.setStanding(false);
    return;
  }
  if (target == "FIRE") {
    mainWindow->setDescription("I burned myself.");
    if (!playerObj.setHealth(playerObj.getHealth() - 20)) {
      msgHandlerObj.gameOverMsg(mainWindow, "HEALTH");
    }
    return;
  }
  mainWindow->setDescription("I couldn't sit there.");
}

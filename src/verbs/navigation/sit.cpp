#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"

void VerbHandler::sit(MainWindow *mainWindow, QString target,
                      Location *location) {
  QMap<QString, std::function<void()>> sitCamp{
      {{"FIRE", [mainWindow, this]() { sitOnFireAtCamp(mainWindow); }},
       {"LOG", [mainWindow, this]() { sitOnLogAtCamp(mainWindow); }}}};

  QMap<QString, QMap<QString, std::function<void()>>> sitLocations{
      {"Camp", sitCamp}};

  if (!sitLocations.contains(location->getName())) {
    mainWindow->setDescription(
        msgHandlerObj.invalidLocation("sit on anything"));
    return;
  }
  if (!sitLocations.contains(location->getName())) {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("sit anywhere"));
    return;
  }
  if (sitLocations[location->getName()].contains(target)) {
    sitLocations[location->getName()][target]();
    return;
  }
  mainWindow->setDescription(msgHandlerObj.invalidLocation("sit"));
}

void VerbHandler::sitOnFireAtCamp(MainWindow *mainWindow) {
  mainWindow->setDescription("I burned myself.");
  if (!playerObj.setHealth(playerObj.getHealth() - 20)) {
    mainWindow->endGame("HEALTH");
  }
}

void VerbHandler::sitOnLogAtCamp(MainWindow *mainWindow) {
  mainWindow->setDescription("I felt a bit cozier sitting by the fire.");
  playerObj.setStanding(false);
}

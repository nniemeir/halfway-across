#include "core/handling/msghandler.h"
#include "core/handling/verbhandler.h"
#include "core/world.h"
#include "entities/player.h"

void VerbHandler::move(MainWindow *mainWindow, QString target,
                       Location *location) {
  if (!worldObj.validDirection(target)) {
    mainWindow->setDescription(QString("%1 was not a direction I was aware of.")
                                   .arg(target.toLower()));
    return;
  }

  if (!playerObj.getStanding()) {
    mainWindow->setDescription("I had to stand up first.");
    return;
  }

  if (worldObj.getCurrentWeather() == "snowing heavily") {
    mainWindow->setDescription(
        "I couldn't risk traveling in such a blizzard.\n");
    return;
  }

  QMap<QString, std::function<bool()>> moveLocations{
      {"Camp",
       [mainWindow, target, this]() { return moveCamp(mainWindow, target); }},
      {"The forest path",
       [mainWindow, target, this]() {
         return moveForestPath(mainWindow, target);
       }},
      {"The dark cave",
       [mainWindow, target, this]() { return moveCave(mainWindow, target); }},
      {"The cave's entrance",
       [mainWindow, target, this]() {
         return moveCaveEntrance(mainWindow, target);
       }},
      {"The well-lit cave",
       [mainWindow, target, this]() {
         return moveCaveLit(mainWindow, target);
       }},
      {"The lake",
       [mainWindow, target, this]() { return moveLake(mainWindow, target); }},
      {"The valley", [mainWindow, target, this]() {
         return moveValley(mainWindow, target);
       }}};
  if (!moveLocations.contains(location->getName())) {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("move anywhere"));
    return;
  }

  bool dirValidInLocation = moveLocations[location->getName()]();
  if (!dirValidInLocation) {
    mainWindow->setDescription(msgHandlerObj.invalidDirection("move", target));
  }
}

bool VerbHandler::moveCamp(MainWindow *mainWindow, QString target) {
  if (target == "NORTH" || target == "N") {
    if (!playerObj.getEnergized()) {
      mainWindow->setDescription(MsgHandler::TIRED);
      return true;
    }

    mainWindow->playSfx("qrc:/audio/sfx/moveSnow.mp3");
    mainWindow->setLocation(camp.getMusicPath(), camp.getAmbiencePath(),
                            &forestPath);
    return true;
  }

  return false;
}

bool VerbHandler::moveForestPath(MainWindow *mainWindow, QString target) {
  if (target == "SOUTH" || target == "S") {
    mainWindow->playSfx("qrc:/audio/sfx/moveStone.mp3");
    mainWindow->setLocation(forestPath.getMusicPath(),
                            forestPath.getAmbiencePath(), &camp);
    return true;
  }
  if (!playerObj.getEnergized()) {
    mainWindow->setDescription(MsgHandler::TIRED);
    return true;
  }

  if (target == "WEST" || target == "W") {
    mainWindow->playSfx("qrc:/audio/sfx/moveSnow.mp3");
    mainWindow->setLocation(forestPath.getMusicPath(),
                            forestPath.getAmbiencePath(), &lake);
    playerObj.setEnergized(false);
    return true;
  }

  if (target == "EAST" || target == "E") {
    mainWindow->playSfx("qrc:/audio/sfx/moveSnow.mp3");
    mainWindow->setLocation(forestPath.getMusicPath(),
                            forestPath.getAmbiencePath(), &caveEntrance);
    playerObj.setEnergized(false);
    return true;
  }

  if (target == "NORTH" || target == "N") {
    mainWindow->playSfx("qrc:/audio/sfx/moveSnow.mp3");
    mainWindow->setLocation(forestPath.getMusicPath(),
                            forestPath.getAmbiencePath(), &valley);
    playerObj.setEnergized(false);
    return true;
  }

  return false;
}

bool VerbHandler::moveCave(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    mainWindow->playSfx("qrc:/audio/sfx/moveSnow.mp3");
    mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                            &caveEntrance);
    return true;
  }
  return false;
}

bool VerbHandler::moveCaveLit(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    mainWindow->playSfx("qrc:/audio/sfx/moveSnow.mp3");
    mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                            &caveEntrance);
    return true;
  }
  return false;
}

bool VerbHandler::moveCaveEntrance(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    mainWindow->playSfx("qrc:/audio/sfx/moveSnow.mp3");
    mainWindow->setLocation(caveEntrance.getMusicPath(),
                            caveEntrance.getAmbiencePath(), &forestPath);
    return true;
  }

  if (target == "EAST" || target == "E") {
    mainWindow->playSfx("qrc:/audio/sfx/moveStone.mp3");

    mainWindow->setLocation(caveEntrance.getMusicPath(),
                            caveEntrance.getAmbiencePath(), &cave);
    return true;
  }

  return false;
}

bool VerbHandler::moveLake(MainWindow *mainWindow, QString target) {
  if (target == "EAST" || target == "E") {
    mainWindow->playSfx("qrc:/audio/sfx/moveSnow.mp3");
    mainWindow->setLocation(lake.getMusicPath(), lake.getAmbiencePath(),
                            &forestPath);
    return true;
  }
  return false;
}

bool VerbHandler::moveValley(MainWindow *mainWindow, QString target) {
  if (target == "SOUTH" || target == "S") {
    mainWindow->playSfx("qrc:/audio/sfx/moveSnow.mp3");
    mainWindow->setLocation(valley.getMusicPath(), valley.getAmbiencePath(),
                            &forestPath);
    return true;
  }
  return false;
}

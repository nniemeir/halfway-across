#include "../../../include/core/audio.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/player.h"

void VerbHandler::move(MainWindow *mainWindow, QString target,
                    Location *location) {
  QMap<QString, std::function<void()>> moveLocations{
      {"Camp", [mainWindow, target, this]() { moveCamp(mainWindow, target); }},
      {"The forest path",
       [mainWindow, target, this]() { moveForestPath(mainWindow, target); }},
      {"The dark cave",
       [mainWindow, target, this]() { moveCave(mainWindow, target); }},
      {"The cave's entrance",
       [mainWindow, target, this]() { moveCaveEntrance(mainWindow, target); }},
      {"The well-lit cave",
       [mainWindow, target, this]() { moveCaveLit(mainWindow, target); }},
      {"The lake",
       [mainWindow, target, this]() { moveLake(mainWindow, target); }},
      {"The valley",
       [mainWindow, target, this]() { moveValley(mainWindow, target); }}};
  if (!playerObj.getStanding()) {
    mainWindow->setDescription("I had to stand up first.");
    return;
  }
  if (!worldObj.validDirection(target)) {
    mainWindow->setDescription(QString("%1 was not a direction I was aware of.")
                                   .arg(target.toLower()));
    return;
  }
  if (!moveLocations.contains(location->getName())) {
    msgHandlerObj.notAllowedInLocMsg(mainWindow, "move anywhere");
    return;
  }
  moveLocations[location->getName()]();
}

void VerbHandler::moveCamp(MainWindow *mainWindow, QString target) {
  if (target == "NORTH" || target == "N") {
    if (worldObj.getCurrentWeather() == "snowing heavily") {
      mainWindow->setDescription(
          "I couldn't risk traveling in such a blizzard.\n");
      return;
    }
    if (!playerObj.getEnergized()) {
      msgHandlerObj.tiredMsg(mainWindow);
      return;
    }
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(camp.getMusicPath(), camp.getAmbiencePath(),
                            &forestPath);
    return;
  }
  msgHandlerObj.notAllowedDirMsg(mainWindow, "move", target);
}

void VerbHandler::moveForestPath(MainWindow *mainWindow, QString target) {
  if (target == "SOUTH" || target == "S") {
    sfxPlayer.play("qrc:/audio/sfx/moveStone.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(forestPath.getMusicPath(),
                            forestPath.getAmbiencePath(), &camp);
    return;
  }
  if (!playerObj.getEnergized()) {
   msgHandlerObj.tiredMsg(mainWindow);
    return;
  }
  if (target == "WEST" || target == "W") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(forestPath.getMusicPath(),
                            forestPath.getAmbiencePath(), &lake);
    playerObj.setEnergized(false);
    return;
  }
  if (target == "EAST" || target == "E") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(forestPath.getMusicPath(),
                            forestPath.getAmbiencePath(), &caveEntrance);
    playerObj.setEnergized(false);
    return;
  }
  if (target == "NORTH" || target == "N") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(forestPath.getMusicPath(),
                            forestPath.getAmbiencePath(), &valley);
    playerObj.setEnergized(false);
    return;
  }
  msgHandlerObj.notAllowedDirMsg(mainWindow, "move", target);
}

void VerbHandler::moveCave(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                            &caveEntrance);
    return;
  }
  msgHandlerObj.notAllowedDirMsg(mainWindow, "move", target);
}

void VerbHandler::moveCaveLit(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                            &caveEntrance);
    return;
  }
  msgHandlerObj.notAllowedDirMsg(mainWindow, "move", target);
}

void VerbHandler::moveCaveEntrance(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(caveEntrance.getMusicPath(),
                            caveEntrance.getAmbiencePath(), &forestPath);
    return;
  }
  if (target == "EAST" || target == "E") {
    sfxPlayer.play("qrc:/audio/sfx/moveStone.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(caveEntrance.getMusicPath(),
                            caveEntrance.getAmbiencePath(), &cave);
    return;
  }
  msgHandlerObj.notAllowedDirMsg(mainWindow, "move", target);
}

void VerbHandler::moveLake(MainWindow *mainWindow, QString target) {
  if (target == "EAST" || target == "E") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(lake.getMusicPath(), lake.getAmbiencePath(),
                            &forestPath);
    return;
  }
  msgHandlerObj.notAllowedDirMsg(mainWindow, "move", target);
}

void VerbHandler::moveValley(MainWindow *mainWindow, QString target) {
  if (target == "SOUTH" || target == "S") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(valley.getMusicPath(), valley.getAmbiencePath(),
                            &forestPath);
    return;
  }
  msgHandlerObj.notAllowedDirMsg(mainWindow, "move", target);
}

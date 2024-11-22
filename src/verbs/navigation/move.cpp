#include "../../../include/core/audio.h"
#include "../../../include/core/handling.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/player.h"

void Handling::move(MainWindow *mainWindow, QString target,
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
  if (playerObj.getStanding()) {
    if (worldObj.validDirection(target)) {
      if (moveLocations.contains(location->getName())) {
        moveLocations[location->getName()]();
      } else {
        notAllowedInLocMsg(mainWindow, "move anywhere");
      }
    } else {
      mainWindow->setDescription(
          QString("%1 was not a direction I was aware of.")
              .arg(target.toLower()));
    }
  } else {
    mainWindow->setDescription("I had to stand up first.");
  }
}

void Handling::moveCamp(MainWindow *mainWindow, QString target) {
  if (target == "NORTH" || target == "N") {
    if (worldObj.getCurrentWeather() == "snowing heavily") {
      mainWindow->setDescription(
          "I couldn't risk traveling in such a blizzard.\n");
    } else if (!playerObj.getEnergized()) {
      tiredMsg(mainWindow);
    } else {
      sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                     0);
      mainWindow->setLocation(camp.getMusicPath(), camp.getAmbiencePath(),
                              &forestPath);
    }
  } else {
    notAllowedDirMsg(mainWindow, "move", target);
  }
}

void Handling::moveForestPath(MainWindow *mainWindow, QString target) {
  if (target == "SOUTH" || target == "S") {
    sfxPlayer.play("qrc:/audio/sfx/moveStone.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(forestPath.getMusicPath(),
                            forestPath.getAmbiencePath(), &camp);
  } else if (playerObj.getEnergized()) {
    if (target == "WEST" || target == "W") {
      sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                     0);
      mainWindow->setLocation(forestPath.getMusicPath(),
                              forestPath.getAmbiencePath(), &lake);
      playerObj.setEnergized(false);
    } else if (target == "EAST" || target == "E") {
      sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                     0);
      mainWindow->setLocation(forestPath.getMusicPath(),
                              forestPath.getAmbiencePath(), &caveEntrance);
      playerObj.setEnergized(false);
    } else if (target == "NORTH" || target == "N") {
      sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                     0);
      mainWindow->setLocation(forestPath.getMusicPath(),
                              forestPath.getAmbiencePath(), &valley);
      playerObj.setEnergized(false);
    } else {
      notAllowedDirMsg(mainWindow, "move", target);
    }
  } else {
    tiredMsg(mainWindow);
  }
}

void Handling::moveCave(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                            &caveEntrance);
  } else {
    notAllowedDirMsg(mainWindow, "move", target);
  }
}

void Handling::moveCaveLit(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                            &caveEntrance);
  } else {
    notAllowedDirMsg(mainWindow, "move", target);
  }
}

void Handling::moveCaveEntrance(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(caveEntrance.getMusicPath(),
                            caveEntrance.getAmbiencePath(), &forestPath);
  } else if (target == "EAST" || target == "E") {
    sfxPlayer.play("qrc:/audio/sfx/moveStone.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(caveEntrance.getMusicPath(),
                            caveEntrance.getAmbiencePath(), &cave);
  } else {
    notAllowedDirMsg(mainWindow, "move", target);
  }
}

void Handling::moveLake(MainWindow *mainWindow, QString target) {
  if (target == "EAST" || target == "E") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(lake.getMusicPath(), lake.getAmbiencePath(),
                            &forestPath);
  } else {
    notAllowedDirMsg(mainWindow, "move", target);
  }
}

void Handling::moveValley(MainWindow *mainWindow, QString target) {
  if (target == "SOUTH" || target == "S") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                   false);
    mainWindow->setLocation(valley.getMusicPath(), valley.getAmbiencePath(),
                            &forestPath);
  } else {
    notAllowedDirMsg(mainWindow, "move", target);
  }
}
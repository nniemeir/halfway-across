#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::move(MainWindow *mainWindow, QString target,
                    Location *location) {
  QMap<QString, std::function<void()>> actions;
  actions["camp"] = [mainWindow, target, this]() {
    moveCamp(mainWindow, target);
  };
  actions["campPath"] = [mainWindow, target, this]() {
    moveCampPath(mainWindow, target);
  };
  actions["cave"] = [mainWindow, target, this]() {
    moveCave(mainWindow, target);
  };
  actions["caveEntrance"] = [mainWindow, target, this]() {
    moveCaveEntrance(mainWindow, target);
  };
  actions["caveLit"] = [mainWindow, target, this]() {
    moveCaveLit(mainWindow, target);
  };
  actions["lake"] = [mainWindow, target, this]() {
    moveLake(mainWindow, target);
  };
  actions["valley"] = [mainWindow, target, this]() {
    moveValley(mainWindow, target);
  };

  if (player.getStanding() == 1) {
    if (world.validDirection(target)) {
      if (actions.contains(location->getName())) {
        actions[location->getName()]();
      } else {
        mainWindow->setDescription(QString("I couldn't do that there."));
      }
    } else {
      mainWindow->setDescription(QString("%1 was not a direction I was aware of.")
                                     .arg(target.toLower()));
    }
  } else {
    mainWindow->setDescription("I had to stand up first.");
  }
}

void Handling::moveCamp(MainWindow *mainWindow, QString target) {
  if (target == "NORTH" || target == "N") {
    int canTravel = world.travelChecks();
    switch (canTravel) {
    case world.TRAVEL_BLIZZARD:
      mainWindow->setDescription(
          "I couldn't risk traveling in such a blizzard.\n");
      break;
    case world.TRAVEL_TIRED:
      mainWindow->setDescription(
          "I did not have the energy to travel anywhere else that day.\n");
      break;
    case world.TRAVEL_YES:
      sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                     0);
      mainWindow->setLocation(camp.getMusicPath(), camp.getAmbiencePath(),
                              &campPath);
      break;
    }
  } else {
    mainWindow->setDescription(
        QString("I couldn't move %1 there.\n").arg(target.toLower()));
  }
}

void Handling::moveCampPath(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(campPath.getMusicPath(), campPath.getAmbiencePath(),
                            &lake);
    player.setEnergy(0);
  } else if (target == "EAST" || target == "E") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(campPath.getMusicPath(), campPath.getAmbiencePath(),
                            &caveEntrance);
    player.setEnergy(0);
  } else if (target == "NORTH" || target == "N") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(campPath.getMusicPath(), campPath.getAmbiencePath(),
                            &valley);
    player.setEnergy(0);
  } else if (target == "SOUTH" || target == "S") {
    sfxPlayer.play("qrc:/audio/sfx/moveStone.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(campPath.getMusicPath(), campPath.getAmbiencePath(),
                            &camp);
  } else {
    mainWindow->setDescription(
        QString("I couldn't move %1 there.\n").arg(target.toLower()));
  }
}

void Handling::moveCave(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                            &caveEntrance);
  } else {
    mainWindow->setDescription(
        QString("I couldn't move %1 there.\n").arg(target.toLower()));
  }
}

void Handling::moveCaveLit(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(cave.getMusicPath(), cave.getAmbiencePath(),
                            &caveEntrance);
  } else {
    mainWindow->setDescription(
        QString("I couldn't move %1 there.\n").arg(target.toLower()));
  }
}

void Handling::moveCaveEntrance(MainWindow *mainWindow, QString target) {
  if (target == "WEST" || target == "W") {

    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(caveEntrance.getMusicPath(),
                            caveEntrance.getAmbiencePath(), &campPath);
  } else if (target == "EAST" || target == "E") {
    sfxPlayer.play("qrc:/audio/sfx/moveStone.mp3", sfxPlayer.getdefSfxVol(), 0);

    mainWindow->setLocation(caveEntrance.getMusicPath(),
                            caveEntrance.getAmbiencePath(), &cave);
  } else {
    mainWindow->setDescription(
        QString("I couldn't move %1 there.\n").arg(target.toLower()));
  }
}

void Handling::moveLake(MainWindow *mainWindow, QString target) {
  if (target == "EAST" || target == "E") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(lake.getMusicPath(), lake.getAmbiencePath(),
                            &campPath);
  } else {
    mainWindow->setDescription(
        QString("I couldn't move %1 there.\n").arg(target.toLower()));
  }
}

void Handling::moveValley(MainWindow *mainWindow, QString target) {
  if (target == "SOUTH" || target == "S") {
    sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(valley.getMusicPath(), valley.getAmbiencePath(),
                            &campPath);
  } else {
    mainWindow->setDescription(
        QString("I couldn't move %1 there.\n").arg(target.toLower()));
  }
}

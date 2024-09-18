#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::look(MainWindow *mainWindow, QString target,
                    Location *location) {
  QMap<QString, std::function<void()>> lookLocations;
  lookLocations["camp"] = [mainWindow, target, this]() {
    lookCamp(mainWindow, target);
  };
  lookLocations["campPath"] = [mainWindow, target, this]() {
    lookCampPath(mainWindow, target);
  };
  lookLocations["cave"] = [mainWindow, target, this]() {
    lookCave(mainWindow, target);
  };
  lookLocations["caveEntrance"] = [mainWindow, target, this]() {
    lookCaveEntrance(mainWindow, target);
  };
  lookLocations["lake"] = [mainWindow, target, this]() {
    lookLake(mainWindow, target);
  };
  lookLocations["valley"] = [mainWindow, target, this]() {
    lookValley(mainWindow, target);
  };

  if (lookLocations.contains(location->getName())) {
    lookLocations[location->getName()]();
  } else {
    mainWindow->setDescription("I couldn't look at anything there.");
  }
}

void Handling::lookCamp(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", camp.getDescription()},
      {"BAG", player.bagInventory()},
      {"FIRE", "The fire burned low."},
      {"BED", "The bed seemed to be quite worn."},
      {"GROUND", camp.locInventory()},
      {"SELF", player.clothesInventory()},
      {"UP",
       "The cave ceiling seemed sturdy enough that it wouldn't collapse on me."},
      {"DOWN", camp.locInventory()},
      {"OUTSIDE",
       QString("It was %1 outside.").arg(world.getCurrentWeather().toLower())}};

  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
    mainWindow->setDescription(
        QString("I couldn't look %1 there.\n").arg(target.toLower()));
  }
}

void Handling::lookCampPath(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", campPath.getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", campPath.locInventory()},
      {"PATH", "The other branches of the path went off into the distance.\n"},
      {"UP", "The sky seemed empty that day."},
      {"DOWN", campPath.locInventory()},
      {"SELF", player.clothesInventory()}};

  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
    mainWindow->setDescription(
        QString("I couldn't look %1 there.\n").arg(target.toLower()));
  }
}

void Handling::lookCave(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", valley.getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", cave.locInventory()},
      {"UP",
       "The cave ceiling seemed sturdy enough that it wouldn't collapse on me."},
      {"DOWN", cave.locInventory()},
      {"SELF", player.clothesInventory()}};
  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
    mainWindow->setDescription(
        QString("I couldn't look %1 there.\n").arg(target.toLower()));
  }
}

void Handling::lookCaveEntrance(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", caveEntrance.getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", caveEntrance.locInventory()},
      {"UP", "I felt smaller looking at the mountain."},
      {"DOWN", caveEntrance.locInventory()},
      {"SELF", player.clothesInventory()}};
  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
    mainWindow->setDescription(
        QString("I couldn't look %1 there.\n").arg(target.toLower()));
  }
}

void Handling::lookLake(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", lake.getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", lake.locInventory()},
      {"LAKE", "The lake had frozen over.\n"},
      {"MOUNTAIN", "Who knew what that mountain held?\n"},
      {"UP", "The sky felt empty that day."},
      {"DOWN", lake.locInventory()},
      {"SELF", player.clothesInventory()}};

  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
    mainWindow->setDescription(
        QString("I couldn't look %1 there.\n").arg(target.toLower()));
  }
}

void Handling::lookValley(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", valley.getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", valley.locInventory()},
      {"TREES", "The trees were covered in snow."},
      {"UP", "The sky felt empty that day."},
      {"DOWN", valley.locInventory()},
      {"SELF", player.clothesInventory()}};
  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
    mainWindow->setDescription(
        QString("I couldn't look %1 there.\n").arg(target.toLower()));
  }
}

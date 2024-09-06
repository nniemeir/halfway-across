#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void handling::look(MainWindow *mainWindow, QString target,
                    Location *location) {
  if (location->getName() == "camp") {
    lookCamp(mainWindow, target);
  } else if (location->getName() == "campPath") {
    lookCampPath(mainWindow, target, location);
  } else if (location->getName() == "cave") {
    lookCave(mainWindow, target);
  } else if (location->getName() == "caveEntrance") {
    lookCaveEntrance(mainWindow, target);
  } else if (location->getName() == "lake") {
    lookLake(mainWindow, target);
  } else if (location->getName() == "valley") {
    lookValley(mainWindow, target);
  } else {
    mainWindow->setDescription("You can't do that here.");
  }
}

void handling::lookCamp(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", camp.getDescription()},
      {"FIRE", "The fire burns low."},
      {"BED", "The bed seems to be quite worn."},
      {"CHEST", "The rusty chest contains your belongings."},
      {"GROUND", camp.locInventory()},
      {"IN BAG", player.bagInventory()},
      {"SELF", player.clothesInventory()},
      {"OUTSIDE",
       QString("It is %1 outside.").arg(world.getCurrentWeather().toLower())}};

  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
      mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

void handling::lookCampPath(MainWindow *mainWindow, QString target,
                            Location *location) {
  QMap<QString, QString> descriptions = {
      {"AROUND", location->getDescription()},
      {"GROUND", location->locInventory()},
      {"PATH", "The other branches of the path go off into the distance.\n"},
      {"IN BAG", player.bagInventory()},
      {"SELF", player.clothesInventory()}};

  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
      mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

void handling::lookCave(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", valley.getDescription()},
      {"GROUND", cave.locInventory()},

      {"IN BAG", player.bagInventory()},
      {"SELF", player.clothesInventory()}};
  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
    mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

void handling::lookCaveEntrance(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", caveEntrance.getDescription()},
      {"GROUND", caveEntrance.locInventory()},

      {"IN BAG", player.bagInventory()},
      {"SELF", player.clothesInventory()}};
  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
      mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

void handling::lookLake(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", lake.getDescription()},
      {"GROUND", lake.locInventory()},
      {"LAKE", "The lake has frozen over.\n"},
      {"MOUNTAIN", "Who knows whthmountain holds?\n"},
      {"IN BAG", player.bagInventory()},
      {"SELF", player.clothesInventory()}};

  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
      mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

void handling::lookValley(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", valley.getDescription()},
      {"GROUND", valley.locInventory()},
      {"TREES", "The trees are covered in snow."},

      {"IN BAG", player.bagInventory()},
      {"SELF", player.clothesInventory()}};
  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
      mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::look(MainWindow *mainWindow, QString target,
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

void Handling::lookCamp(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", camp.getDescription()},
      {"BAG", player.bagInventory()},
      {"FIRE", "The fire burns low."},
      {"BED", "The bed seems to be quite worn."},
      {"CHEST", "The rusty chest contains your belongings."},
      {"GROUND", camp.locInventory()},
      {"SELF", player.clothesInventory()},
      {"OUTSIDE",
       QString("It is %1 outside.").arg(world.getCurrentWeather().toLower())}};

  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
      mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

void Handling::lookCampPath(MainWindow *mainWindow, QString target,
                            Location *location) {
  QMap<QString, QString> descriptions = {
      {"AROUND", location->getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", location->locInventory()},
      {"PATH", "The other branches of the path go off into the distance.\n"},
      {"SELF", player.clothesInventory()}};

  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
      mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

void Handling::lookCave(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", valley.getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", cave.locInventory()},
      {"SELF", player.clothesInventory()}};
  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
    mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

void Handling::lookCaveEntrance(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", caveEntrance.getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", caveEntrance.locInventory()},
      {"SELF", player.clothesInventory()}};
  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
      mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

void Handling::lookLake(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", lake.getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", lake.locInventory()},
      {"LAKE", "The lake has frozen over.\n"},
      {"MOUNTAIN", "Who knows whthmountain holds?\n"},
      {"SELF", player.clothesInventory()}};

  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
      mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

void Handling::lookValley(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", valley.getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", valley.locInventory()},
      {"TREES", "The trees are covered in snow."},
      {"SELF", player.clothesInventory()}};
  if (descriptions.contains(target)) {
    mainWindow->setDescription(descriptions.value(target));
  } else {
      mainWindow->setDescription(QString("You can't look %1 here.\n").arg(target.toLower()));
  }
}

#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::look(MainWindow *mainWindow, QString target,
                    Location *location) {
    QMap<QString, std::function<void()>> actions;
    actions["camp"] = [mainWindow, target, this]() {     lookCamp(mainWindow, target);};
    actions["campPath"] = [mainWindow, target, this]() {     lookCampPath(mainWindow, target);};
    actions["cave"] = [mainWindow, target, this]() {     lookCave(mainWindow, target);};
    actions["caveEntrance"] = [mainWindow, target, this]() {     lookCaveEntrance(mainWindow, target);};
    actions["lake"] = [mainWindow, target, this]() {     lookLake(mainWindow, target);};
    actions["valley"] = [mainWindow, target, this]() {     lookValley(mainWindow, target);};

    if (actions.contains(location->getName())) {
        actions[location->getName()]();
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

void Handling::lookCampPath(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", campPath.getDescription()},
      {"BAG", player.bagInventory()},
      {"GROUND", campPath.locInventory()},
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
      {"MOUNTAIN", "Who knows what this mountain holds?\n"},
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

#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/characters.h"
#include "../../../include/entities/player.h"

void VerbHandler::look(MainWindow *mainWindow, QString target,
                       Location *location) {
  if (ensembleObj.isCharacterName(target)) {
    if (worldObj.getActiveCharacter() == nullptr) {
      mainWindow->setDescription(MsgHandler::CHARACTER_NOT_ACTIVE);
      return;
    }
    if (QString::compare(target, worldObj.getActiveCharacter()->getName(),
                         Qt::CaseInsensitive) == 1 &&
        worldObj.getActiveCharacter()->getLocation() ==
            worldObj.getCurrentLocation()->getName()) {
      mainWindow->setDescription(MsgHandler::CHARACTER_NOT_ACTIVE);
      return;
    }
    mainWindow->setDescription(worldObj.getActiveCharacter()->getDescription());
    return;
  }

  QMap<QString, std::function<void()>> lookLocations{
      {"Camp", [mainWindow, target, this]() { lookCamp(mainWindow, target); }},
      {"The forest path",
       [mainWindow, target, this]() { lookForestPath(mainWindow, target); }},
      {"The dark cave",
       [mainWindow, target, this]() { lookCave(mainWindow, target); }},
      {"The cave's entrance",
       [mainWindow, target, this]() { lookCaveEntrance(mainWindow, target); }},
      {"The lake",
       [mainWindow, target, this]() { lookLake(mainWindow, target); }},
      {"The valley",
       [mainWindow, target, this]() { lookValley(mainWindow, target); }}};

  if (!lookLocations.contains(location->getName())) {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("look anywhere"));
    return;
  }
  lookLocations[location->getName()]();
}

void VerbHandler::lookCamp(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", camp.getDescription()},
      {"BAG", playerObj.displayBagInventory()},
      {"FIRE", "The fire burned low."},
      {"BED", "The bed seemed to be quite worn."},
      {"GROUND", camp.displayItems()},
      {"SELF", playerObj.displayClothesInventory()},
      {"UP", "The cave ceiling seemed sturdy enough that it wouldn't collapse "
             "on me."},
      {"DOWN", camp.displayItems()},
      {"OUTSIDE", QString("It was %1 outside.")
                      .arg(worldObj.getCurrentWeather().toLower())}};

  if (!descriptions.contains(target)) {
    mainWindow->setDescription(msgHandlerObj.invalidDirection("look", target));
    return;
  }
  mainWindow->setDescription(descriptions.value(target));
}

void VerbHandler::lookForestPath(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", forestPath.getDescription()},
      {"BAG", playerObj.displayBagInventory()},
      {"GROUND", forestPath.displayItems()},
      {"PATH", "The other branches of the path went off into the distance.\n"},
      {"UP", "The sky seemed empty that day."},
      {"DOWN", forestPath.displayItems()},
      {"SELF", playerObj.displayClothesInventory()}};

  if (!descriptions.contains(target)) {
    mainWindow->setDescription(msgHandlerObj.invalidDirection("look", target));
    return;
  }
  mainWindow->setDescription(descriptions.value(target));
}

void VerbHandler::lookCave(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", valley.getDescription()},
      {"BAG", playerObj.displayBagInventory()},
      {"GROUND", cave.displayItems()},
      {"UP", "The cave ceiling seemed sturdy enough that it wouldn't collapse "
             "on me."},
      {"DOWN", cave.displayItems()},
      {"SELF", playerObj.displayClothesInventory()}};

  if (!descriptions.contains(target)) {
    mainWindow->setDescription(msgHandlerObj.invalidDirection("look", target));
    return;
  }
  mainWindow->setDescription(descriptions.value(target));
}

void VerbHandler::lookCaveEntrance(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", caveEntrance.getDescription()},
      {"BAG", playerObj.displayBagInventory()},
      {"GROUND", caveEntrance.displayItems()},
      {"UP", "I felt smaller looking at the mountain."},
      {"DOWN", caveEntrance.displayItems()},
      {"SELF", playerObj.displayClothesInventory()}};

  if (!descriptions.contains(target)) {
    mainWindow->setDescription(msgHandlerObj.invalidDirection("look", target));
    return;
  }
  mainWindow->setDescription(descriptions.value(target));
}

void VerbHandler::lookLake(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", lake.getDescription()},
      {"BAG", playerObj.displayBagInventory()},
      {"GROUND", lake.displayItems()},
      {"LAKE", "The lake had frozen over.\n"},
      {"MOUNTAIN", "Who knew what that mountain held?\n"},
      {"UP", "The sky felt empty that day."},
      {"DOWN", lake.displayItems()},
      {"SELF", playerObj.displayClothesInventory()}};

  if (!descriptions.contains(target)) {
    mainWindow->setDescription(msgHandlerObj.invalidDirection("look", target));
    return;
  }
  mainWindow->setDescription(descriptions.value(target));
}

void VerbHandler::lookValley(MainWindow *mainWindow, QString target) {
  QMap<QString, QString> descriptions = {
      {"AROUND", valley.getDescription()},
      {"BAG", playerObj.displayBagInventory()},
      {"GROUND", valley.displayItems()},
      {"TREES", "The trees were covered in snow."},
      {"UP", "The sky felt empty that day."},
      {"DOWN", valley.displayItems()},
      {"SELF", playerObj.displayClothesInventory()}};

  if (!descriptions.contains(target)) {
    mainWindow->setDescription(msgHandlerObj.invalidDirection("look", target));
    return;
  }
  mainWindow->setDescription(descriptions.value(target));
}

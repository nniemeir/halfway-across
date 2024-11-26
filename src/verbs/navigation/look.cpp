#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/characters.h"
#include "../../../include/entities/player.h"

bool VerbHandler::lookingAtCharacter(MainWindow *mainWindow, QString target,
                                     Location *location) {
  if (!ensembleObj.isCharacterName(target)) {
    return false;
  }
  auto activeCharacter = worldObj.getActiveCharacter();
  if (activeCharacter == nullptr) {
    mainWindow->setDescription(MsgHandler::CHARACTER_NOT_ACTIVE);
    return true;
  }
  if (QString::compare(target, activeCharacter->getName(),
                       Qt::CaseInsensitive) == 1 ||
      activeCharacter->getLocation() == location->getName()) {
    mainWindow->setDescription(MsgHandler::CHARACTER_NOT_ACTIVE);
    return true;
  }
  mainWindow->setDescription(activeCharacter->getDescription());
  return true;
}

void VerbHandler::look(MainWindow *mainWindow, QString target,
                       Location *location) {
  if (lookingAtCharacter(mainWindow, target, location)) {
    return;
  }
  QMap<QString, QString> generalDescriptions = {
      {"AROUND", location->getDescription()},
      {"BAG", playerObj.displayBagInventory()},
      {"GROUND", location->displayItems()},
      {"SELF", playerObj.displayClothesInventory()},
      {"DOWN", location->displayItems()}};
  QMap<QString, QString> campDescriptions = {
      {"FIRE", "The fire burned low."},
      {"BED", "The bed seemed to be quite worn."},
      {"UP", "The cave ceiling seemed sturdy enough that it wouldn't collapse "
             "on me."},
      {"OUTSIDE", QString("It was %1 outside.")
                      .arg(worldObj.getCurrentWeather().toLower())}};

  QMap<QString, QString> forestPathDescriptions = {
      {"PATH", "The other branches of the path went off into the distance.\n"},
      {"UP", "The sky seemed empty that day."}};

  QMap<QString, QString> caveDescriptions = {
      {"UP", "The cave ceiling seemed sturdy enough that it wouldn't collapse "
             "on me."}};
  QMap<QString, QString> darkCaveDescriptions = {{}};
  QMap<QString, QString> caveEntranceDescriptions = {
      {"UP", "I felt smaller looking at the mountain."}};

  QMap<QString, QString> lakeDescriptions = {
      {"LAKE", "The lake had frozen over.\n"},
      {"MOUNTAIN", "Who knew what that mountain held?\n"},
      {"UP", "The sky felt empty that day."}};

  QMap<QString, QString> valleyDescriptions = {
      {"TREES", "The trees were covered in snow."},
      {"UP", "The sky felt empty that day."}};

  QMap<QString, QMap<QString, QString>> locationDescriptionMaps{
      {"Camp", campDescriptions},
      {"The forest path", forestPathDescriptions},
      {"The dark cave", darkCaveDescriptions},
      {"The cave", caveDescriptions},
      {"The lake", lakeDescriptions},
      {"The valley", valleyDescriptions}};

  if (generalDescriptions.contains(target)) {
    mainWindow->setDescription(generalDescriptions.value(target));
    return;
  }
  if (!locationDescriptionMaps.contains(location->getName())) {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("look anywhere"));
    return;
  }
  mainWindow->setDescription(
      locationDescriptionMaps[location->getName()][target]);
}

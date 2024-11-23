#include "../../../include/core/audio.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"

void VerbHandler::read(MainWindow *mainWindow, Location *location,
                    QString target) {
  if (location->getName() == "Perished Menu" ||
      location->getName() == "Introduction Menu") {
    msgHandlerObj.notAllowedInLocMsg(mainWindow, "read");
    return;
  }
  QMap<QString, QString> intangibleItems = {
      {"JOURNAL", playerObj.displayJournal()},
      {"RECIPES", playerObj.displayRecipeBook()}};

  if (!intangibleItems.contains(target)) {
    msgHandlerObj.missingItemMsg(mainWindow, target);
    return;
  }
  sfxPlayer.play("qrc:/audio/sfx/read.mp3", sfxPlayer.getdefSfxVol(), 0);
  mainWindow->setDescription(intangibleItems.value(target));
}

#include "../../../include/core/audio.h"
#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"

// The implementation will be extended to tangible items at a later time
void Handling::read(MainWindow *mainWindow, Location *location,
                    QString target) {
  if (location->getName() == "Perished Menu" ||
      location->getName() == "Introduction Menu") {
    notAllowedInLocMsg(mainWindow, "read");
  } else {
    QMap<QString, QString> intangibleItems = {
        {"JOURNAL", playerObj.displayJournal()},
        {"RECIPES", playerObj.displayRecipeBook()}};

    if (intangibleItems.contains(target)) {
      sfxPlayer.play("qrc:/audio/sfx/read.mp3", sfxPlayer.getdefSfxVol(), 0);
      mainWindow->setDescription(intangibleItems.value(target));
    } else {
      missingItemMsg(mainWindow, target);
    }
  }
}

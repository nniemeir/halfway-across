#include "../../../include/core/audio.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"

void VerbHandler::goodbye(MainWindow *mainWindow, Location *location) {
  sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                 false);
  mainWindow->setCompassImage(location->getCompassPath());
  mainWindow->setLocationImage(location->getImagePath());
  mainWindow->setDescription("You set off on your way once again.");
  worldObj.setConversing(false);
  worldObj.setConversedtoday(true);
  worldObj.getActiveCharacter()->incrementTimesEncountered();
}

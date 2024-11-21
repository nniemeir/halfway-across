#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/world.h"

void Handling::goodbye(MainWindow *mainWindow, Location *location) {
  sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(),
                 false);
  mainWindow->setCompassImage(location->getCompass());
  mainWindow->setLocationImage(location->getImage());
  mainWindow->setDescription("You set off on your way once again.");
  worldObj.setGreetedNPC(false);
  worldObj.setSocialized(true);
  worldObj.getActiveCharacter()->incrementTimesEncountered();
}

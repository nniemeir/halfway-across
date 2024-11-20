#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/world.h"

void Handling::goodbye(MainWindow *mainWindow, Location *location) {
  sfxPlayer.play("qrc:/audio/sfx/moveSnow.mp3", sfxPlayer.getdefSfxVol(), 0);
  mainWindow->setCompassImage(location->getCompass());
  mainWindow->setSettingImage(location->getImage());
  mainWindow->setDescription("You set off on your way once again.");
  worldObj.setGreetedNPC(0);
  worldObj.setSocialized(1);
}

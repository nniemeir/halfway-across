#include "core/handling/verbhandler.h"
#include "core/world.h"

void VerbHandler::goodbye(MainWindow *mainWindow, Location *location) {
  mainWindow->playSfx("qrc:/audio/sfx/moveSnow.mp3");
  mainWindow->setCompassImage(location->getCompassPath());
  mainWindow->setLocationImage(location->getImagePath());
  mainWindow->setDescription("You set off on your way once again.");
  worldObj.setConversing(false);
  worldObj.setConversedToday(true);
  worldObj.getActiveCharacter()->incrementTimesEncountered();
}

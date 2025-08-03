#include "core/handling/msghandler.h"
#include "core/handling/verbhandler.h"
#include "entities/player.h"

void VerbHandler::begin(MainWindow *mainWindow, Location *location) {
  if (location->getName() != "Introduction Menu") {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("begin"));
    return;
  }
  mainWindow->playSfx("qrc:/audio/sfx/write.mp3");
  mainWindow->setLocation(intro.getMusicPath(), intro.getAmbiencePath(), &camp);
  mainWindow->setDescription(playerObj.displayJournal());
}

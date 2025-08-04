#include "core/handling/msghandler.h"
#include "core/handling/verbhandler.h"
#include "entities/player.h"

void VerbHandler::begin(MainWindow *mainWindow, Location *location) {
  if (location->getName() != "Introduction Menu") {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("begin"));
    return;
  }

  mainWindow->setLocation(intro.getMusicPath(), intro.getAmbiencePath(), &camp);

  mainWindow->playSfx("qrc:/audio/sfx/write.mp3");
  mainWindow->setDescription(playerObj.displayJournal());
}

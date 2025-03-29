#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"

void VerbHandler::begin(MainWindow *mainWindow, Location *location) {
  if (location->getName() != "Introduction Menu") {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("begin"));
    return;
  }
  mainWindow->playSfx("qrc:/audio/sfx/write.mp3");
  mainWindow->setLocation(intro.getMusicPath(), intro.getAmbiencePath(), &camp);
  mainWindow->setDescription(playerObj.displayJournal());
}

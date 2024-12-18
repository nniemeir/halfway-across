#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"

void VerbHandler::diagnose(MainWindow *mainWindow, Location *location) {
  if (location->getName() == "Perished Menu" ||
      location->getName() == "Introduction Menu") {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("reflect"));
    return;
  }
  mainWindow->setDescription(playerObj.generateWarnings());
}

#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/survival/hunting.h"

void VerbHandler::yell(MainWindow *mainWindow, Location *location) {
  if (huntingObj.getActiveAnimal() == "BEAR") {
    mainWindow->endGame("HEALTH");
    return;
  }
  huntingObj.setActiveAnimal("");
  mainWindow->setDescription("I let out a sharp cry that alerted surrounding "
                             "animals to my prescence.");
}

#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/survival/hunting.h"

void VerbHandler::yell(MainWindow *mainWindow, Location *location) {
  if (huntingObj.getActiveAnimal() == "BEAR") {
    msgHandlerObj.gameOverMsg(mainWindow, "HEALTH");
    return;
  }
  huntingObj.setActiveAnimal("");
  mainWindow->setDescription("I let out a sharp cry that alerted surrounding "
                             "animals to my prescence.");
}

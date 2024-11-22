#include "../../../include/core/handling.h"
#include "../../../include/survival/hunting.h"

void Handling::yell(MainWindow *mainWindow, Location *location) {
  if (huntingObj.getActiveAnimal() != "BEAR") {
    huntingObj.setActiveAnimal("");
    mainWindow->setDescription("I let out a sharp cry that alerted surrounding "
                               "animals to my prescence.");
  } else {
    gameOverMsg(mainWindow, "HEALTH");
  }
}
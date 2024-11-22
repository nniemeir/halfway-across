#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"

void Handling::diagnose(MainWindow *mainWindow, Location *location) {
  if (location->getName() == "Perished Menu" ||
      location->getName() == "Introduction Menu") {
    notAllowedInLocMsg(mainWindow, "reflect");
  } else {
    mainWindow->setDescription(playerObj.generateWarnings());
  }
}

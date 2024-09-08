#include "../../include/handling.h"
#include "../../include/world.h"

void Handling::sleep(MainWindow *mainWindow,
                     Location *location) {
  if (location->getName() == "camp") {
    mainWindow->setDescription(
        "You close your eyes and another night passes.\n"),
        world.advanceDay();
  } else {
    mainWindow->setDescription("You can't do that here.");
  }
}
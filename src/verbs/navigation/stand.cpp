#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"

void VerbHandler::stand(MainWindow *mainWindow) {
  if (playerObj.getStanding()) {
    mainWindow->setDescription("I was already standing.\n");
    return;
  }
  playerObj.setStanding(true);
  mainWindow->setDescription("I stood up.\n");
}

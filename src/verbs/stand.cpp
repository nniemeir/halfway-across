#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::stand(MainWindow *mainWindow) {
  if (playerObj.getStanding() == 0) {
    playerObj.setStanding(1);
    mainWindow->setDescription("I stood up.\n");
  } else {
    mainWindow->setDescription("I was already standing.\n");
  }
}

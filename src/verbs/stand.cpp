#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::stand(MainWindow *mainWindow) {
  if (player.getStanding() == 0) {
    player.setStanding(1);
    mainWindow->setDescription("I stood up.\n");
  } else {
    mainWindow->setDescription("I was already standing.\n");
  }
}

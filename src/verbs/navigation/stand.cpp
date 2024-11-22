#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"

void Handling::stand(MainWindow *mainWindow) {
  if (!playerObj.getStanding()) {
    playerObj.setStanding(true);
    mainWindow->setDescription("I stood up.\n");
  } else {
    mainWindow->setDescription("I was already standing.\n");
  }
}

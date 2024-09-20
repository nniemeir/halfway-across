#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::cry(MainWindow *mainWindow) {
  if (player.getMental() < 100) {
    player.setMental(player.getMental() + 10);
    mainWindow->setDescription("Crying made me feel a little better.");
  } else {
    mainWindow->setDescription(
        "I was content enough that I didn't feel like crying");
  }
}

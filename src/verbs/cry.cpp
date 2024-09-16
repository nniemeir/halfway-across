#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::cry(MainWindow *mainWindow) {
  player.setMental(player.getMental() + 10);
  mainWindow->setDescription("I felt a little better.");
}

#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::cry(MainWindow *mainWindow) {
  if (playerObj.getMental() < 100) {
    if (playerObj.getCryCooldown() == 0) {
      playerObj.setMental(playerObj.getMental() + 10);
      mainWindow->setDescription("Crying made me feel a little better.");
      playerObj.setCryCooldown(3);
    } else {
      mainWindow->setDescription("I felt too numb to cry.");
    }
  } else {
    mainWindow->setDescription(
        "I was content enough that I didn't feel like crying.");
  }
}

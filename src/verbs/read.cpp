#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"

// This will be fully implemented at a later time
void Handling::read(MainWindow *mainWindow, QString target) {
  if (target == "RECIPES") {
    sfxPlayer.play("qrc:/audio/sfx/read.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setDescription(playerObj.displayRecipeBook());
  } else {
    missingItemMsg(mainWindow, target);
  }
}

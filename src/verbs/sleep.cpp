#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::sleep(MainWindow *mainWindow, Location *location) {
  if (location->getName() == "Camp") {
    sfxPlayer.play("qrc:/audio/sfx/sleep.mp3", sfxPlayer.getdefSfxVol(), 0);
    QString reason = worldObj.advanceDay();
    if (reason != "") {
      gameOverMsg(mainWindow, reason);
    } else {
      sfxPlayer.play("qrc:/audio/sfx/write.mp3", sfxPlayer.getdefSfxVol(), 0);
      mainWindow->setDescription(playerObj.displayJournal());
    }
  } else {
    notAllowedInLocMsg(mainWindow, "sleep safely");
  }
}

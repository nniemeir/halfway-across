#include "../../../include/core/audio.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/player.h"

void VerbHandler::sleep(MainWindow *mainWindow, Location *location) {
  if (location->getName() != "Camp") {
    msgHandlerObj.notAllowedInLocMsg(mainWindow, "sleep safely");
    return;
  }
  sfxPlayer.play("qrc:/audio/sfx/sleep.mp3", sfxPlayer.getdefSfxVol(), 0);
  QString reason = worldObj.advanceDay();
  if (!reason.isEmpty()) {
    msgHandlerObj.gameOverMsg(mainWindow, reason);
    return;
  }
  sfxPlayer.play("qrc:/audio/sfx/write.mp3", sfxPlayer.getdefSfxVol(), 0);
  mainWindow->setDescription(playerObj.displayJournal());
}

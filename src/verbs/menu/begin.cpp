#include "../../../include/core/audio.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"

void VerbHandler::begin(MainWindow *mainWindow, Location *location) {
  if (location->getName() != "Introduction Menu") {
    msgHandlerObj.notAllowedInLocMsg(mainWindow, "begin");
    return;
  }
  sfxPlayer.play("qrc:/audio/sfx/write.mp3", sfxPlayer.getdefSfxVol(), false);
  mainWindow->setLocation(intro.getMusicPath(), intro.getAmbiencePath(), &camp);
  mainWindow->setDescription(playerObj.displayJournal());
}

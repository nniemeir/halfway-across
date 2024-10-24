#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::begin(MainWindow *mainWindow, Location *location) {
  if (location->getName() == "Introduction Menu") {
    sfxPlayer.play("qrc:/audio/sfx/write.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setLocation(intro.getMusicPath(), intro.getAmbiencePath(),
                            &camp);
    mainWindow->setDescription(playerObj.displayJournal());
  } else {
    notAllowedInLocMsg(mainWindow, "begin");
  }
}

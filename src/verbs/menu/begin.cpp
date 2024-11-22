#include "../../../include/core/audio.h"
#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"

void Handling::begin(MainWindow *mainWindow, Location *location) {
  if (location->getName() == "Introduction Menu") {
    sfxPlayer.play("qrc:/audio/sfx/write.mp3", sfxPlayer.getdefSfxVol(), false);
    mainWindow->setLocation(intro.getMusicPath(), intro.getAmbiencePath(),
                            &camp);
    mainWindow->setDescription(playerObj.displayJournal());
  } else {
    notAllowedInLocMsg(mainWindow, "begin");
  }
}

#include "../../include/audio.h"
#include "../../include/handling.h"

void handling::begin(MainWindow *mainWindow,
                     Location *location) {
  if (location->getName() == "intro") {
    sfxPlayer.play("qrc:/audio/sfx/lanternRustle.mp3", sfxPlayer.getdefSfxVol(), 0);

    mainWindow->setLocation(intro.getMusicPath(), intro.getAmbiencePath(),
                            &camp);
  } else {
    mainWindow->setDescription("You can't do that here.");
  }
}

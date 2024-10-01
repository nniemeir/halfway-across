#include "../../include/audio.h"
#include "../../include/handling.h"

void Handling::begin(MainWindow *mainWindow, Location *location) {
  if (location->getName() == "Introduction Menu") {
    sfxPlayer.play("qrc:/audio/sfx/lanternRustle.mp3", sfxPlayer.getdefSfxVol(),
                   0);

    mainWindow->setLocation(intro.getMusicPath(), intro.getAmbiencePath(),
                            &camp);
  } else {
    mainWindow->setDescription("My thoughts weren't making any sense.");
  }
}

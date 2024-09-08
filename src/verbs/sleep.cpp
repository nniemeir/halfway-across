#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/world.h"

void Handling::sleep(MainWindow *mainWindow,
                     Location *location) {
  if (location->getName() == "camp") {
    sfxPlayer.play("qrc:/audio/sfx/sleep.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setDescription(
        "You close your eyes and another night passes.\n"),
        world.advanceDay();
  } else {
    mainWindow->setDescription("You can't do that here.");
  }
}

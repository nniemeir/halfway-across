#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/world.h"

void Handling::sleep(MainWindow *mainWindow, Location *location) {
  if (location->getName() == "camp") {
    sfxPlayer.play("qrc:/audio/sfx/sleep.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setDescription("I closed my eyes and another night passed.\n");
    if (world.advanceDay()) {
      mainWindow->setLocation(camp.getMusicPath(), camp.getAmbiencePath(),
                              &perished);
    }
  } else {
    mainWindow->setDescription("I felt fairly tired, but I couldn't sleep there.");
  }
}

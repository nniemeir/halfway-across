#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/world.h"

void Handling::sleep(MainWindow *mainWindow, Location *location)
{
  if (location->getName() == "Camp")
  {
    sfxPlayer.play("qrc:/audio/sfx/sleep.mp3", sfxPlayer.getdefSfxVol(), 0);
    mainWindow->setDescription("I closed my eyes and another night passed.\n");
    QString reason = world.advanceDay();
    if (reason != "")
    {
      gameOverMsg(mainWindow, reason);
    }
  }
  else
  {
    notAllowedInLocMsg(mainWindow, "sleep safely");
  }
}

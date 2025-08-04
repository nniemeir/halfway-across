#include "core/handling/msghandler.h"
#include "core/handling/verbhandler.h"
#include "core/world.h"
#include "entities/player.h"

void VerbHandler::sleep(MainWindow *mainWindow, Location *location) {
  if (location->getName() != "Camp") {
    mainWindow->setDescription(msgHandlerObj.invalidLocation("sleep safely"));
    return;
  }

  mainWindow->playSfx("qrc:/audio/sfx/sleep.mp3");
  QString reason = worldObj.advanceDay();
  if (!reason.isEmpty()) {
    mainWindow->endGame(reason);
    return;
  }

  mainWindow->playSfx("qrc:/audio/sfx/write.mp3");
  mainWindow->setDescription(playerObj.displayJournal());
}

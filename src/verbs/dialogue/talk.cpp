#include "core/handling/encounterhandler.h"
#include "core/handling/msghandler.h"
#include "core/handling/verbhandler.h"
#include "core/world.h"

void VerbHandler::talk(MainWindow *mainWindow, QString verb, QString target,
                       QString subject, Location *location) {
  auto activeCharacter = worldObj.getActiveCharacter();
  if (activeCharacter == nullptr) {
    mainWindow->setDescription(MsgHandler::CHARACTER_NOT_ACTIVE);
    return;
  }
  if (QString::compare(target, activeCharacter->getName(),
                       Qt::CaseInsensitive) == 1) {
    mainWindow->setDescription(MsgHandler::CHARACTER_NOT_ACTIVE);
    return;
  }
  if (!worldObj.getConversing()) {
    mainWindow->setDescription(MsgHandler::CHARACTER_NOT_ACTIVE);
    return;
  }
  encounterHandlerObj.talkLogic(mainWindow, verb, target, subject, location);
}

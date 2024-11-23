#include "../../../include/core/handling/encounterhandler.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"

void VerbHandler::talk(MainWindow *mainWindow, QString verb, QString target,
                    QString subject, Location *location) {
  auto activeCharacter = worldObj.getActiveCharacter();
  if (activeCharacter == nullptr) {
    msgHandlerObj.characterNotActiveMsg(mainWindow, target);
    return;
  }
  if (QString::compare(target, activeCharacter->getName(),
                       Qt::CaseInsensitive) == 1) {
    msgHandlerObj.characterNotActiveMsg(mainWindow, target);
    return;
  }
  if (!worldObj.getGreetedNPC()) {
    msgHandlerObj.notGreetedMsg(mainWindow);
    return;
  }
  encounterHandlerObj.talkLogic(mainWindow, verb, target, subject, location);
}

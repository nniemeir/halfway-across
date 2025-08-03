#include "utils/script.h"
#include "core/handling/verbhandler.h"

void VerbHandler::script(MainWindow *mainWindow) {
  scriptObj.setStatus(true);
  mainWindow->setDescription("It seemed important to record my actions.");
}

void VerbHandler::unscript(MainWindow *mainWindow) {
  scriptObj.setStatus(false);
  mainWindow->setDescription(
      "It didn't seem important to keep a record of my actions.");
}

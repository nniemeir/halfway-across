#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/utils/script.h"

void VerbHandler::script(MainWindow *mainWindow) {
  scriptObj.setRecordingStatus(true);
  mainWindow->setDescription("It seemed important to record my actions.");
}

void VerbHandler::unscript(MainWindow *mainWindow) {
  scriptObj.setRecordingStatus(false);
  mainWindow->setDescription(
      "It didn't seem important to keep a record of my actions.");
}

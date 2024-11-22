#include "../../../include/core/handling.h"
#include "../../../include/utils/script.h"

void Handling::script(MainWindow *mainWindow) {
  scriptObj.setRecordingStatus(true);
  mainWindow->setDescription("It seemed important to record my actions.");
}

void Handling::unscript(MainWindow *mainWindow) {
  scriptObj.setRecordingStatus(false);
  mainWindow->setDescription(
      "It didn't seem important to keep a record of my actions.");
}

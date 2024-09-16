#include "../../include/handling.h"
#include "../../include/mainwindow.h"
#include "../../include/journal.h"

void Handling::script(MainWindow *mainWindow) {
  transcript.setRecordingStatus(true);
  mainWindow->setDescription("It seemed important to record my actions.");
}

void Handling::unscript(MainWindow *mainWindow) {
  transcript.setRecordingStatus(false);
  mainWindow->setDescription(
      "It didn't seem important to keep a record of my actions.");
}

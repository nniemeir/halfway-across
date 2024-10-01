#include "../../include/handling.h"
#include "../../include/journal.h"
#include "../../include/mainwindow.h"

void Handling::script(MainWindow *mainWindow) {
  journalObj.setRecordingStatus(true);
  mainWindow->setDescription("It seemed important to record my actions.");
}

void Handling::unscript(MainWindow *mainWindow) {
  journalObj.setRecordingStatus(false);
  mainWindow->setDescription(
      "It didn't seem important to keep a record of my actions.");
}

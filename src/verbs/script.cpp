#include "../../include/handling.h"
#include "../../include/mainwindow.h"
#include "../../include/transcript.h"

void Handling::script(MainWindow *mainWindow) {
    transcript.setRecordingStatus(true);
    mainWindow->setDescription("It seems important to record your actions.");
}

void Handling::unscript(MainWindow *mainWindow) {
    transcript.setRecordingStatus(false);
    mainWindow->setDescription("It doesn't seem important to keep a record of this.");
}

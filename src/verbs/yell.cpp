#include "../../include/handling.h"
#include "../../include/mainwindow.h"
#include "../../include/world.h"

void Handling::yell(MainWindow *mainWindow) {
    world.setConspicuous(true);
    mainWindow->setDescription("You let out a sharp cry that alerts surrounding animals to your prescence.");
}

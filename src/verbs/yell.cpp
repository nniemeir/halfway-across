#include "../../include/handling.h"
#include "../../include/mainwindow.h"
#include "../../include/world.h"

void Handling::yell(MainWindow *mainWindow) {
  world.setConspicuous(true);
  mainWindow->setDescription(
      "I let out a sharp cry that alerted surrounding animals to my prescence.");
}

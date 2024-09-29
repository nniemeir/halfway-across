#include "../../include/handling.h"
#include "../../include/mainwindow.h"
#include "../../include/player.h"

void Handling::yell(MainWindow *mainWindow)
{
  player.setConspicuous(true);
  mainWindow->setDescription("I let out a sharp cry that alerted surrounding "
                             "animals to my prescence.");
}

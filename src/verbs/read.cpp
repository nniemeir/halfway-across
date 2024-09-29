#include "../../include/handling.h"
#include "../../include/player.h"

// This will be fully implemented at a later time
void Handling::read(MainWindow *mainWindow, QString target)
{
  if (target == "RECIPES")
  {
    mainWindow->setDescription(player.showRecipeBook());
  }
  else
  {
    missingItemMsg(mainWindow, target);
  }
}

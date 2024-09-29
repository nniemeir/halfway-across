#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::sit(MainWindow *mainWindow, QString target, Location *location)
{

  QMap<QString, std::function<void()>> sitLocations;
  sitLocations["Camp"] = [mainWindow, target, this]()
  {
    sitCamp(mainWindow, target);
  };

  if (sitLocations.contains(location->getName()))
  {
    sitLocations[location->getName()]();
  }
  else
  {
    notAllowedInLocMsg(mainWindow, "sit on anything");
  }
}

void Handling::sitCamp(MainWindow *mainWindow, QString target)
{
  if (target == "LOG")
  {
    mainWindow->setDescription("I felt a bit cozier sitting by the fire.");
    player.setStanding(0);
  }
  else if (target == "FIRE")
  {
    mainWindow->setDescription("I burned myself.");
    if (player.setHealth(player.getHealth() - 20))
    {
      gameOverMsg(mainWindow, "HEALTH");
    }
  }
  else
  {
    mainWindow->setDescription("I couldn't sit there.");
  }
}

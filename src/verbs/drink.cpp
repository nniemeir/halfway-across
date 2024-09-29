#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::drink(MainWindow *mainWindow, QString target,
                     Location *location)
{

  QMap<QString, std::function<void()>> drinkLocations;
  drinkLocations["The lake"] = [mainWindow, target, this]()
  {
    drinkLake(mainWindow, target);
  };

  if (drinkLocations.contains(location->getName()))
  {
    drinkLocations[location->getName()]();
  }
  else
  {
    notAllowedInLocMsg(mainWindow, "drink anything");
  }
}

void Handling::drinkLake(MainWindow *mainWindow, QString target)
{
  if (target == "LAKE")
  {
    if (world.getChiseledIce() == 1)
    {
      if (player.getThirst() < 100)
      {
        sfxPlayer.play("qrc:/audio/sfx/drink.mp3", sfxPlayer.getdefSfxVol(), 0);
        mainWindow->setDescription(
            "I felt more refreshed after drinking some cold water.");
        player.setThirst(player.getThirst() + 20);
      }
      else
      {
        mainWindow->setDescription("I wasn't thirsty.");
      }
    }
    else
    {
      mainWindow->setDescription("The lake was frozen over.");
    }
  }
  else
  {
    mainWindow->setDescription(
        QString("I couldn't drink from %1.").arg(target.toLower()));
  }
}

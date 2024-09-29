#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"

void Handling::wait(MainWindow *mainWindow, Location *location)
{

  QMap<QString, std::function<void()>> waitLocations;
  waitLocations["The lake"] = [mainWindow, this]()
  { waitLake(mainWindow); };

  if (waitLocations.contains(location->getName()))
  {
    waitLocations[location->getName()]();
  }
  else
  {
    notAllowedInLocMsg(mainWindow, "wait safely");
  }
}

void Handling::waitLake(MainWindow *mainWindow)
{
  int rodIndex =
      inventoryObj.searchInventory(player.getInventory(), "FISHING ROD");
  if (rodIndex != -1)
  {
    waitFishing(mainWindow, rodIndex);
  }
  else
  {
    waitMsg(mainWindow);
  }
}

void Handling::waitFishing(MainWindow *mainWindow, int rodIndex)
{
  if (inventoryObj.getInventoryItem(player.getInventory(), rodIndex)
          .getActive() == 1)
  {
    QString generatedFish = world.generateFish();
    int itemIndex =
        inventoryObj.searchInventory(world.getFishInventory(), generatedFish);
    if (itemIndex != -1)
    {
      sfxPlayer.play("qrc:/audio/sfx/fishReel.mp3", sfxPlayer.getdefSfxVol(),
                     0);
      mainWindow->setDescription(
          QString("I caught a %1!\n")
              .arg(inventoryObj
                       .getInventoryItem(world.getFishInventory(), itemIndex)
                       .getName()
                       .toLower()));
      int playerItemIndex =
          inventoryObj.searchInventory(player.getInventory(), generatedFish);
      inventoryObj.addItem(
          player.getInventory(),
          inventoryObj.getInventoryItem(world.getFishInventory(), itemIndex),
          playerItemIndex);
    }
    inventoryObj.getInventoryItem(player.getInventory(), rodIndex).setActive(0);
  }
  else
  {
    waitMsg(mainWindow);
  }
}

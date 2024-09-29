#include "../../include/handling.h"
#include "../../include/hunting.h"
#include "../../include/player.h"

void Handling::skin(MainWindow *mainWindow, QString target, Location *location)
{
    int animalIndex = inventoryObj.searchInventory(location->getInventory(), target);
    int knifeIndex = inventoryObj.searchInventory(player.getInventory(), "HUNTING KNIFE");
    if (knifeIndex != -1)
    {
        if (animalIndex != -1)
        {
            hunting.skinAnimal(mainWindow, target);
            mainWindow->setDescription(QString("I skinned the %1.").arg(target.toLower()));
        }
        else
        {
            mainWindow->setDescription(QString("There wasn't a slain %1 in the area for me to skin.").arg(target.toLower()));
        }
    }
    else
    {
        mainWindow->setDescription("I needed a knife to skin an animal.");
    }
}

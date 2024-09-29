#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/hunting.h"
#include "../../include/player.h"

void Handling::shoot(MainWindow *mainWindow, QString target, Location *location)
{
    int bowIndex = inventoryObj.searchInventory(player.getInventory(), "BOW");
    int arrowIndex =
        inventoryObj.searchInventory(player.getInventory(), "ARROW");
    if (bowIndex != -1 && arrowIndex != -1)
    {
        if (target == hunting.getActiveAnimal())
        {
            sfxPlayer.play("qrc:/audio/sfx/arrow.mp3", sfxPlayer.getdefSfxVol(), 0);
            bool hit = hunting.hitTarget(target);
            if (!hunting.recoveredArrow(hit))
            {
                inventoryObj.removeItem(player.getInventory(), arrowIndex);
            }
            if (hit)
            {
                if (hunting.assessDamage(target))
                {
                    mainWindow->setDescription(QString("I managed to fell the %1.").arg(target.toLower()));
                    int databaseAnimalIndex = inventoryObj.searchInventory(hunting.getSlainAnimals(), target);
                    int locationAnimalIndex = inventoryObj.searchInventory(location->getInventory(), target);
                    Item animal = inventoryObj.getInventoryItem(hunting.getSlainAnimals(), databaseAnimalIndex);
                    inventoryObj.addItem(location->getInventory(), animal, locationAnimalIndex);
                    hunting.setActiveAnimal("");
                }
            }
        }
        else
        {
            mainWindow->setDescription(QString("I didn't see %1 %2 in the area.").arg(handle.getArticle(target).arg(target)));
        }
    }
    else
    {
        mainWindow->setDescription("I couldn't shoot without a bow and arrow.");
    }
}

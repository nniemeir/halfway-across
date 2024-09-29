#include "../../include/handling.h"
#include "../../include/hunting.h"
#include "../../include/player.h"
#include "../../include/world.h"

Hunting::Hunting()
{

    bearParts = {{"BEAR FAT", 1, 1, 0, "FAT", "NONE", "I could cook it to get rendered fat."},
                 {"BEAR MEAT", 1, 1, 50, "RAW MEAT", "NONE", "If cooked, it could provide a filling meal."},
                 {"BEAR PELT", 1, 1, 0, "PELT", "NONE", "I could use it for crafting."}};

    deerParts = {{"DEER FAT", 1, 1, 0, "FAT", "NONE", "I could cook it to get rendered fat."},
                 {"DEER MEAT", 1, 1, 30, "RAW MEAT", "NONE", "If cooked, it could ease my hunger."},
                 {"DEER PELT", 1, 1, 0, "PELT", "NONE", "I could use it for crafting."}};

    foxParts = {{"FOX FAT", 1, 1, 0, "FAT", "NONE", "I could cook it to get rendered fat."},
                {"FOX MEAT", 1, 1, 20, "RAW MEAT", "NONE", "If cooked, it could provide some nourishment."},
                {"FOX PELT", 1, 1, 0, "PELT", "NONE", "I could use it for crafting."}};

    rabbitParts = {{"RABBIT FAT", 1, 1, 0, "FAT", "NONE", "I could cook it to get rendered fat."},
                   {"RABBIT MEAT", 1, 1, 15, "RAW MEAT", "NONE", "If cooked, it could slightly ease my hunger."},
                   {"RABBIT PELT", 1, 1, 0, "PELT", "NONE", "I could use it for crafting."}};

    validAnimals = {"BEAR", "DEER", "FOX", "RABBIT"};

    slainAnimals = {{"BEAR", 1, 0, 0, "ANIMALS", "NONE", "The slain bear almost looks bigger on the ground."},
                    {"DEER", 1, 0, 0, "ANIMALS", "NONE", "It was a lean doe."},
                    {"FOX", 1, 0, 0, "ANIMALS", "NONE", "It wouldn't provide much meat."},
                    {"RABBIT", 1, 0, 0, "ANIMALS", "NONE", "It would provide very little meat."}};
}

Hunting hunting;

void Hunting::hunt(MainWindow *mainWindow, QString target,
                   Location *location)
{
    if (location->getName() == "The valley")
    {
        int bowIndex = inventoryObj.searchInventory(player.getInventory(), "BOW");
        int arrowIndex =
            inventoryObj.searchInventory(player.getInventory(), "ARROW");
        if (bowIndex != -1 && arrowIndex != -1)
        {
            if (std::find(validAnimals.begin(), validAnimals.end(), target) != validAnimals.end())
            {
                if (foundAnimal(target))
                {
                    huntScenario(mainWindow, target, arrowIndex);
                }
                else
                {
                    mainWindow->setDescription(
                        QString("I was unable to find %1 %2 in the valley.")
                            .arg(handle.getArticle(target))
                            .arg(target.toLower()));
                }
            }
            else
            {
                mainWindow->setDescription(QString("It didn't seem like a good idea to hunt %1").arg(target.toLower()));
            }
        }
        else
        {
            mainWindow->setDescription("I needed a bow and arrow to hunt.");
        }
    }
    else
    {
        mainWindow->setDescription(QString("%1 didn't seem like a good place to hunt.").arg(location->getName()));
    }
}

// This function will be expanded to calculate where the animal was hit and deduct health accordingly
bool Hunting::assessDamage(QString target)
{
    return true;
}

QString Hunting::getActiveAnimal() const
{
    return activeAnimal;
}

void Hunting::setActiveAnimal(QString animal)
{
    activeAnimal = animal;
}

// This function will be expanded to calculate if a shot hits the animal based on its size
bool Hunting::hitTarget(QString target)
{
    return true;
}

std::vector<Item> &Hunting::getSlainAnimals() { return slainAnimals; }

bool Hunting::recoveredArrow(bool hitTarget)
{
    int chance;
    if (hitTarget)
    {
        chance = 30;
    }
    else
    {
        chance = 65;
    }
    if (world.roll(chance))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Hunting::skinAnimal(MainWindow *mainWindow, QString target)
{
    QMap<QString, std::vector<Item>> animalParts = {{"BEAR", bearParts},
                                                    {"DEER", deerParts},
                                                    {"FOX", foxParts},
                                                    {"RABBIT", rabbitParts}};

    if (animalParts.contains(target))
    {
        inventoryObj.addLoot(player.getInventory(), animalParts.value(target));
    }
}

void Hunting::huntScenario(MainWindow *mainWindow, QString target, int arrowIndex)
{
    mainWindow->setDescription(QString(
                                   "I spotted %1 %2.")
                                   .arg(handle.getArticle(target))
                                   .arg(target.toLower()));
    activeAnimal = target;
}

bool Hunting::foundAnimal(QString target)
{
    QMap<QString, int> probabilities = {{"BEAR", 5}, {"DEER", 40}, {"FOX", 20}, {"RABBIT", 35}};
    int chance;
    if (probabilities.contains(target))
    {
        chance = probabilities.value(target);
    }
    if (world.roll(chance))
    {
        return true;
    }
    else
    {
        return false;
    }
}

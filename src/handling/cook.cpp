#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/item.h"


void handling::cook(MainWindow *mainWindow, QString target, Location *location) {
    if (location->getName() == "camp") {
        int itemIndex = player.searchInventory(target);
        if (itemIndex!= -1) {
            if (player.getItemType(itemIndex) == "RAW MEAT") {
                mainWindow->setDescription(QString("You cook the %1.").arg(target.toLower()));
                item cooker;
                item cookedItem = cooker.makeCookedVersion(player.getInventoryItem(itemIndex));
                int cookedIndex = player.searchInventory(cookedItem.name);
                player.addItem(cookedItem, cookedIndex);
            } else {
                mainWindow->setDescription("You can't cook that.");
            }
            } else {
                mainWindow->setDescription(QString("You don't have any %1").arg(target.toLower()));
            }
        } else {
        mainWindow->setDescription("You need to be near a campfire to cook");
    }
}

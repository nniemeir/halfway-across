#include "../../include/handling.h"
#include "../../include/item.h"
#include "../../include/player.h"

void Handling::cook(MainWindow *mainWindow, QString target, Location *location) {
    if (location->getName() == "camp") {
        int itemIndex = inventoryObj.searchInventory(player.getInventory(), target);
        if (itemIndex!= -1) {
            if (inventoryObj.getItemType(player.getInventory(), itemIndex) == "RAW MEAT") {
                mainWindow->setDescription(QString("You cook the %1.").arg(target.toLower()));
                item cooker;
                item cookedItem = cooker.makeCookedVersion(inventoryObj.getInventoryItem(player.getInventory(), itemIndex));
                int cookedIndex = inventoryObj.searchInventory(player.getInventory(), cookedItem.name);
                inventoryObj.addItem(player.getInventory(), cookedItem, cookedIndex);
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

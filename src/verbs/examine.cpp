#include "../../include/handling.h"
#include "../../include/player.h"

void Handling::examine(MainWindow *mainWindow, QString target) {
    int targetIndex = inventoryObj.searchInventory(player.getInventory(), target);
    if (targetIndex != -1) {
        QString description =
            inventoryObj.getInventoryItem(player.getInventory(), targetIndex)
                .getDescription();
        mainWindow->setDescription(description);
    }
    else {
        mainWindow->setDescription(QString("I didn't have %1 %2 in my possession.")
                                       .arg(handle.getArticle(target))
                                       .arg(target.toLower()));
    }
}

#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"

void handling::eat(MainWindow *mainWindow, QString target) {
    int itemIndex = inventoryObj.searchInventory(player.getInventory(), target);
    if (itemIndex!= -1) {
        if (inventoryObj.getItemType(player.getInventory(), itemIndex) == "FOOD") {
            sfxPlayer.play("qrc:/audio/sfx/eat.mp3", sfxPlayer.getdefSfxVol(), 0);
        mainWindow->setDescription(
            QString("You eat the %1.").arg(inventoryObj.getItemName(player.getInventory(), itemIndex).toLower()));
        player.setHunger(player.getHunger() + inventoryObj.getItemEffect(player.getInventory(), itemIndex));
        inventoryObj.removeItem(player.getInventory(), itemIndex);
        } else {
            mainWindow->setDescription(QString("You can't eat %1.").arg(target.toLower()));
        }
    } else {
        mainWindow->setDescription(QString("You don't have a %1.").arg(target.toLower()));
    }
}

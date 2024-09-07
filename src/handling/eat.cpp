#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/audio.h"

void handling::eat(MainWindow *mainWindow, QString target) {
    int itemIndex = player.searchInventory(target);
    if (itemIndex!= -1) {
        if (player.getItemType(itemIndex) == "FOOD") {
            sfxPlayer.play("qrc:/audio/sfx/eat.mp3", sfxPlayer.getdefSfxVol(), 0);
        mainWindow->setDescription(
            QString("You eat the %1.").arg(player.getItemName(itemIndex).toLower()));
        player.setHunger(player.getHunger() + player.getItemEffect(itemIndex));
        player.removeItem(itemIndex);
        } else {
            mainWindow->setDescription(QString("You can't eat %1.").arg(target.toLower()));
        }
    } else {
        mainWindow->setDescription(QString("You don't have a %1.").arg(target.toLower()));
    }
}

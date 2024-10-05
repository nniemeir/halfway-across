#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/hunting.h"
#include "../../include/player.h"

void Handling::hunt(MainWindow *mainWindow, QString target,
                    Location *location) {
  if (huntingObj.getDailyHunts() < 2) {
    if (location->getName() == "The valley") {
      int bowIndex =
          inventoryObj.searchInventory(playerObj.getInventory(), "BOW");
      int arrowIndex =
          inventoryObj.searchInventory(playerObj.getInventory(), "ARROW");
      if (bowIndex != -1 && arrowIndex != -1) {
        int huntResult = huntingObj.activity(target, arrowIndex);
        switch (huntResult) {
        case 0:
          sfxPlayer.play("qrc:/audio/sfx/hunt.mp3", sfxPlayer.getdefSfxVol(),
                         0);
          mainWindow->setDescription(
              QString("I spotted %1 %2.")
                  .arg(handlingObj.getArticle(target), target.toLower()));
          break;
        case 1:
          mainWindow->setDescription(
              QString("I was unable to find %1 %2 in the valley.")
                  .arg(handlingObj.getArticle(target), target.toLower()));
          break;
        case 2:
          mainWindow->setDescription(
              QString(
                  "I thought of hunting %1, but it didn't seem reasonable in "
                  "the area.")
                  .arg(target.toLower()));
          break;
        }
      } else {
        mainWindow->setDescription("I needed a bow and arrow to hunt.");
      }
    } else {
      mainWindow->setDescription(
          QString("%1 didn't seem like a good place to hunt.")
              .arg(location->getName()));
    }
  } else {
    mainWindow->setDescription("I was too tired to hunt anymore that day.");
  }
}

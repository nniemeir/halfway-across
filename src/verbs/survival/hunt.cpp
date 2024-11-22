#include "../../../include/core/audio.h"
#include "../../../include/core/handling.h"
#include "../../../include/entities/player.h"
#include "../../../include/survival/hunting.h"

void Handling::hunt(MainWindow *mainWindow, QString target,
                    Location *location) {
  if (huntingObj.getDailyHunts() < 2) {
    if (huntingObj.getActiveAnimal() != target) {
      if (location->getName() == "The valley") {
        int bowIndex =
            inventoryObj.searchInventory(playerObj.getInventory(), "BOW");
        int arrowIndex =
            inventoryObj.searchInventory(playerObj.getInventory(), "ARROW");
        if (bowIndex != ITEM_NOT_FOUND && arrowIndex != ITEM_NOT_FOUND) {
          int huntResult = huntingObj.activity(target, arrowIndex);
          switch (huntResult) {
          case Hunting::ANIMAL_FOUND:
            sfxPlayer.play("qrc:/audio/sfx/hunt.mp3", sfxPlayer.getdefSfxVol(),
                           false);
            mainWindow->setDescription(
                QString("I spotted %1 %2.")
                    .arg(handlingObj.getArticle(target), target.toLower()));
            huntingObj.setActiveAnimal(target);
            break;
          case Hunting::ANIMAL_NOT_FOUND:
            mainWindow->setDescription(
                QString("I was unable to find %1 %2 in the valley.")
                    .arg(handlingObj.getArticle(target), target.toLower()));
            break;
          case Hunting::ANIMAL_INVALID:
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
      mainWindow->setDescription(
          QString("I was already hunting %1 %2.")
              .arg(getArticle(target), target.toLower()));
    }
  } else {
    mainWindow->setDescription("I was too tired to hunt anymore that day.");
  }
}

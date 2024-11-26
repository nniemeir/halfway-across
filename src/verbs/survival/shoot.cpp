#include "../../../include/core/audio.h"
#include "../../../include/core/handling/inputhandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/entities/player.h"
#include "../../../include/survival/hunting.h"

void VerbHandler::shoot(MainWindow *mainWindow, QString target,
                        Location *location) {
  int bowIndex = inventoryObj.searchInventory(playerObj.getInventory(), "BOW");
  int arrowIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "ARROW");
  if (bowIndex == ITEM_NOT_FOUND || arrowIndex == ITEM_NOT_FOUND) {
    mainWindow->setDescription("I couldn't shoot without a bow and arrow.");
    return;
  }
  if (target != huntingObj.getActiveAnimal()) {
    mainWindow->setDescription(
        QString("I didn't see %1 %2 in the area.")
            .arg(inputHandlerObj.getArticle(target), target.toLower()));
    return;
  }
  sfxPlayer.play("qrc:/audio/sfx/arrow.mp3", sfxPlayer.getdefSfxVol(), 0);
  bool hit = huntingObj.hitTarget(target);
  if (!huntingObj.recoveredArrow(hit)) {
    inventoryObj.removeItem(playerObj.getInventory(), arrowIndex);
  }
  if (!hit) {
    mainWindow->setDescription(
        QString("The %1 managed to escape me after I shot it.")
            .arg(target.toLower()));
    huntingObj.setActiveAnimal("");
    return;
  }
  if (!huntingObj.assessDamage(target)) {
    mainWindow->setDescription(
        QString("I failed to hit the %1.").arg(target.toLower()));
    return;
  }
  mainWindow->setDescription(
      QString("I managed to fell the %1.").arg(target.toLower()));
  int databaseAnimalIndex =
      inventoryObj.searchInventory(huntingObj.getSlainAnimals(), target);
  int locationAnimalIndex =
      inventoryObj.searchInventory(location->getInventory(), target);
  Item animal = inventoryObj.getInventoryItem(huntingObj.getSlainAnimals(),
                                              databaseAnimalIndex);
  inventoryObj.addItem(location->getInventory(), animal, locationAnimalIndex);
  huntingObj.setActiveAnimal("");
}

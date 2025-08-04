#include "core/handling/inputhandler.h"
#include "core/handling/verbhandler.h"
#include "entities/player.h"
#include "survival/hunting.h"

void VerbHandler::hunt(MainWindow *mainWindow, QString target,
                       Location *location) {
  if (huntingObj.getDailyAttempts() == 2) {
    mainWindow->setDescription("I was too tired to hunt anymore that day.");
    return;
  }

  if (huntingObj.getActiveAnimal() == target) {
    mainWindow->setDescription(
        QString("I was already hunting %1 %2.")
            .arg(inputHandlerObj.getArticle(target), target.toLower()));
    return;
  }

  if (location->getName() != "The valley") {
    mainWindow->setDescription(
        QString("%1 didn't seem like a good place to hunt.")
            .arg(location->getName()));
    return;
  }

  int bowIndex = inventoryObj.searchInventory(playerObj.getInventory(), "BOW");
  int arrowIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), "ARROW");
  if (bowIndex == ITEM_NOT_FOUND || arrowIndex == ITEM_NOT_FOUND) {
    mainWindow->setDescription("I needed a bow and arrow to hunt.");
    return;
  }

  mainWindow->setDescription(huntingObj.processSeekResult(mainWindow, target, arrowIndex));
}

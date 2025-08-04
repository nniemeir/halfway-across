#include "core/handling/inputhandler.h"
#include "core/handling/msghandler.h"
#include "core/handling/verbhandler.h"
#include "entities/locations.h"
#include "entities/player.h"

void VerbHandler::put(MainWindow *mainWindow, QString target, QString subject,
                      Location *location) {
  QMap<QString, std::vector<Item>> inventories = {
      {"GROUND", location->getInventory()}};

  if (!inventories.contains(subject)) {
    mainWindow->setDescription(
        QString("I couldn't put something on the %1.").arg(subject.toLower()));
    return;
  }

  std::vector<Item> destinationInv = inventories.value(subject);
  int itemIndex =
      inventoryObj.searchInventory(playerObj.getInventory(), target);
  if (itemIndex == ITEM_NOT_FOUND) {
    mainWindow->setDescription(msgHandlerObj.missingItem(
        inputHandlerObj.getArticle(target) + " " + target));
    return;
  }

  int locationItemIndex =
      inventoryObj.searchInventory(location->getInventory(), target);
  inventoryObj.addItem(
      location->getInventory(),
      playerObj.getInventoryItem(playerObj.getInventory(), itemIndex),
      locationItemIndex);
  inventoryObj.removeItem(playerObj.getInventory(), itemIndex);

  mainWindow->playSfx("qrc:/audio/sfx/drop.mp3");
  mainWindow->setDescription(QString("I put the %1 on the %2.")
                                 .arg(target.toLower(), subject.toLower()));
}

#include "../../include/handling.h"
#include "../../include/player.h"

// Hunting will be greatly expanded upon in later versions
void Handling::hunt(MainWindow *mainWindow, QString target,
                    Location *location) {
  if (location->getName() == "valley") {
    int bowIndex = inventoryObj.searchInventory(player.getInventory(), "BOW");
    int arrowIndex =
        inventoryObj.searchInventory(player.getInventory(), "ARROW");
    if (bowIndex != -1 && arrowIndex != -1) {
      if (target == "DEER") {
        mainWindow->setDescription("I managed to drop a deer in a single shot.");
        int fatIndex =
            inventoryObj.searchInventory(player.getInventory(), "DEER FAT");
        inventoryObj.addItem(player.getInventory(),
                             {"DEER FAT", 1, 1, 10, "FAT", "NONE"}, fatIndex);
        int meatIndex =
            inventoryObj.searchInventory(player.getInventory(), "DEER MEAT");
        inventoryObj.addItem(player.getInventory(),
                             {"DEER MEAT", 1, 1, 10, "RAW MEAT", "NONE"},
                             meatIndex);
        int peltIndex =
            inventoryObj.searchInventory(player.getInventory(), "DEER PELT");
        inventoryObj.addItem(player.getInventory(),
                             {"DEER PELT", 1, 1, 10, "PELT", "NONE"},
                             peltIndex);
      } else {
        mainWindow->setDescription(
            QString("I couldn't hunt %1.").arg(target.toLower()));
      }
    } else {
      mainWindow->setDescription("I needed a weapon to hunt.");
    }
  } else {
    mainWindow->setDescription("I couldn't hunt there.");
  }
}

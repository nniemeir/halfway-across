#include "../../include/entities/locations.h"

QString Location::getName() const { return name; }

QString Location::getDescription() const { return description; }

QString Location::getCompassPath() const { return compassPath; }

QString Location::getImagePath() const { return imagePath; }

QString Location::getAmbiencePath() const { return ambiencePath; }

QString Location::getMusicPath() const { return musicPath; }

std::vector<Item> &Location::getInventory() { return inventory; }

QString Location::setDescription(QString message) {
  description = message + description;
  return description;
}

QString Location::displayItems() const {
  QStringList inventoryItemsText;
  for (const auto &item : inventory) {
    inventoryItemsText.append(
        QString("%1: %2").arg(item.getName()).arg(item.getAmount()));
  }
  std::sort(inventoryItemsText.begin(), inventoryItemsText.end());
  QString inventoryText;
  if (inventoryItemsText.isEmpty()) {
    inventoryText.append("I didn't see anything of note on the ground.");
    return inventoryText;
  }
  inventoryText.append("Looking at the ground, I saw:\n");
  inventoryText.append(inventoryItemsText.join("\n"));
  return inventoryText;
}

Location camp(
    "Camp",
    "My camp provided some respite from the harsh winds that had been plaguing "
    "me.",
    ":/images/compass/n.png", ":/images/locations/camp.png",
    "qrc:/audio/music/placeholder.mp3", "qrc:/audio/ambience/campfire.mp3",
    {{"ARROW", "I could load it into my bow to hunt at a distance.", "TOOLS",
      "NONE", 3, false, 0, 0},
     {"BOW", "If loaded with an arrow, it could be used for hunting.", "TOOLS",
      "ARROW", 1, false, 0, 0},
     {"CANTEEN", "I could store water in it.", "TOOLS", "NONE", 1, false, 100,
      0},
     {"CHISEL", "I could use it to break through ice.", "TOOLS", "NONE", 1,
      false, 0, 0},
     {"DRIED BEEF", "It could provide some sustenance, but not much else.",
      "FOOD", "NONE", 3, false, 30, 0},
     {"FISHING ROD",
      "If loaded with bait such as rendered fat, I could catch fish with it.",
      "TOOLS", "RENDERED FAT", 1, false, 0, 0},
     {"HARD TACK", "It could provide some sustenance, but not much else.",
      "FOOD", "NONE", 3, false, 20, 0},
     {"HUNTING KNIFE", "I could use this to skin animals.", "TOOLS", "NONE", 1,
      false, 0, 0},
     {"LANTERN",
      "If loaded with a tallow candle, I could use it to light my way.",
      "TOOLS", "TALLOW CANDLE", 1, false, 0, 0}});

Location forestPath(
    "The forest path",
    "I moved through a break in the trees for a while before "
    "reaching a fork in the path.",
    ":/images/compass/news.png", ":/images/locations/forestPath.png",
    "qrc:/audio/music/placeholder.mp3", "qrc:/audio/ambience/mountainWind.mp3",
    {{"PIECE OF WOOD", "I could use it to fuel my campfire or to craft items.",
      "RESOURCES", "NONE", 1, false, 0, 0}});

Location caveEntrance(
    "The cave's entrance",
    "I happened upon a cave, it didn't seem like a good idea to "
    "find out what it contained.",
    ":/images/compass/ew.png", ":/images/locations/caveEntrance.png",
    "qrc:/audio/music/placeholder.mp3", "qrc:/audio/ambience/mountainWind.mp3",
    {{"ROCK", "I could use it to distract animals.", "TOOLS", "NONE", 1, false,
      0, 0}});

Location cave("The dark cave", "Entering the cave, I saw nothing but darkness.",
              ":/images/compass/w.png", ":/images/locations/cave.png",
              "qrc:/audio/music/placeholder.mp3",
              "qrc:/audio/ambience/caveWind.mp3",
              {{"ROCK", "I could use it to distract animals.", "TOOLS", "NONE",
                1, false, 0, 0}});

Location caveLit("The well-lit cave", "My lantern now lit the way.",
                 ":/images/compass/w.png", ":/images/locations/caveLit.png",
                 "qrc:/audio/music/placeholder.mp3",
                 "qrc:/audio/ambience/caveWind.mp3",
                 {{"ROCK", "I could use it to distract animals.", "TOOLS",
                   "NONE", 1, false, 0, 0}});

Location intro("Introduction Menu",
               "HALFWAY ACROSS\n\nType BEGIN to continue.\nType HELP for a "
               "list of commands.",
               "", ":/images/locations/intro.png",
               "qrc:/audio/music/placeholder.mp3", "", {{}});

Location lake("The lake",
              "I arrived at a lake after an hour's journey, it could be a good "
              "source of fish and water.",
              ":/images/compass/e.png", ":/images/locations/lake.png",
              "qrc:/audio/music/placeholder.mp3",
              "qrc:/audio/ambience/mountainWind.mp3",
              {{"PIECE OF WOOD",
                "I could use it to fuel my campfire or to craft items.",
                "RESOURCES", "NONE", 1, false, 0, 0}});

Location perished("Perished Menu", "\n\nType QUIT to exit.", "",
                  ":/images/locations/perished.png",
                  "qrc:/audio/music/placeholder.mp3",
                  "qrc:/audio/ambience/mountainWind.mp3", {{{}}});

Location valley("The valley",
                "I arrived at a clearing. It seemed like a good spot for "
                "hunting.",
                ":/images/compass/s.png", ":/images/locations/valley.png",
                "qrc:/audio/music/placeholder.mp3",
                "qrc:/audio/ambience/mountainWind.mp3",
                {{"FEATHER", "I could use it for crafting.", "RESOURCES",
                  "NONE", 3, false, 0, 0}});

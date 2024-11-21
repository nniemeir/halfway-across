#include "../include/locations.h"

Location::Location(const QString &name, const QString &description,
                   const QString &compass, const QString &image,
                   const QString &musicPath, const QString &ambiencePath,
                   const std::vector<Item> &inventory)
    : name(name), description(description), compass(compass), image(image),
      musicPath(musicPath), ambiencePath(ambiencePath), inventory(inventory) {}

QString Location::getName() const { return name; }
QString Location::getDescription() const { return description; }
QString Location::getCompass() const { return compass; }
QString Location::getImage() const { return image; }
QString Location::getAmbiencePath() const { return ambiencePath; }
QString Location::getMusicPath() const { return musicPath; }
QString Location::setDescription(QString message) {
  description = message + description;
  return description;
}

std::vector<Item> &Location::getInventory() { return inventory; }

QString Location::locInventory() const {
  QStringList inventoryItemsText;
  for (const auto &item : inventory) {
    inventoryItemsText.append(
        QString("%1: %2").arg(item.getName()).arg(item.getAmount()));
  }
  std::sort(inventoryItemsText.begin(), inventoryItemsText.end());
  QString inventoryText;
  if (!inventoryItemsText.isEmpty()) {
    inventoryText.append("Looking at the ground, I saw:\n");
    inventoryText.append(inventoryItemsText.join("\n"));
  } else {
    inventoryText.append("I didn't see anything of note on the ground.");
  }
  return inventoryText;
}

Location camp(
    "Camp",
    "My camp provided some respite from the harsh winds that had been plaguing "
    "me.",
    ":/images/compass/n.png", ":/images/locations/camp.png",
    "qrc:/audio/music/placeholder.mp3", "qrc:/audio/ambience/campfire.mp3",
    {{"ARROW", 3, false, 0, 0, "TOOLS", "NONE",
      "I could load it into my bow to hunt at a distance."},
     {"BOW", 1, false, 0, 0, "TOOLS", "ARROW",
      "If loaded with an arrow, it could be used for hunting."},
     {"CANTEEN", 1, false, 100, 0, "TOOLS", "NONE",
      "I could store water in it."},
     {"CHISEL", 1, false, 0, 0, "TOOLS", "NONE",
      "I could use it to break through ice."},
     {"DRIED BEEF", 3, false, 30, 0, "FOOD", "NONE",
      "It could provide some sustenance, but not much else."},
     {"FISHING ROD", 1, false, 0, 0, "TOOLS", "RENDERED FAT",
      "If loaded with bait such as rendered fat, I could catch fish with it."},
     {"HARD TACK", 3, false, 20, 0, "FOOD", "NONE",
      "It could provide some sustenance, but not much else."},
     {"HUNTING KNIFE", 1, false, 0, 0, "TOOLS", "NONE",
      "I could use this to skin animals."},
     {"LANTERN", 1, false, 0, 0, "TOOLS", "TALLOW CANDLE",
      "If loaded with a tallow candle, I could use it to light my way."}});

Location
    forestPath("The forest path",
               "I moved through a break in the trees for a while before "
               "reaching a fork in the road.",
               ":/images/compass/news.png", ":/images/locations/forestPath.png",
               "qrc:/audio/music/placeholder.mp3",
               "qrc:/audio/ambience/mountainWind.mp3",
               {{"PIECE OF WOOD", 1, false, 0, 0, "RESOURCES", "NONE",
                 "I could use it to fuel my campfire or to craft items."}});

Location caveEntrance(
    "The cave's entrance",
    "I happened upon a cave, it didn't seem like a good idea to "
    "find out what it contained.",
    ":/images/compass/ew.png", ":/images/locations/caveEntrance.png",
    "qrc:/audio/music/placeholder.mp3", "qrc:/audio/ambience/mountainWind.mp3",
    {{"ROCK", 1, false, 0, 0, "TOOLS", "NONE",
      "I could use it to distract animals."}});

Location cave("The dark cave", "Entering the cave, I saw nothing but darkness.",
              ":/images/compass/w.png", ":/images/locations/cave.png",
              "qrc:/audio/music/placeholder.mp3",
              "qrc:/audio/ambience/caveWind.mp3",
              {{"ROCK", 1, false, 0, 0, "TOOLS", "NONE",
                "I could use it to distract animals."}});

Location caveLit("The well-lit cave", "My lantern now lit the way.",
                 ":/images/compass/w.png", ":/images/locations/caveLit.png",
                 "qrc:/audio/music/placeholder.mp3",
                 "qrc:/audio/ambience/caveWind.mp3",
                 {{"ROCK", 1, false, 0, 0, "TOOLS", "NONE",
                   "I could use it to distract animals."}});

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
              {{"PIECE OF WOOD", 1, false, 0, 0, "RESOURCES", "NONE",
                "I could use it to fuel my campfire or to craft items."}});

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
                {{"FEATHER", 3, false, 0, 0, "RESOURCES", "NONE",
                  "I could use it for crafting."}});

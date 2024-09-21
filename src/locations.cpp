#include "../include/locations.h"

Location::Location(const QString &name, const QString &description,
                   const QString &image, const QString &musicPath,
                   const QString &ambiencePath,
                   const std::vector<Item> &inventory)
    : name(name), description(description), image(image), musicPath(musicPath),
      ambiencePath(ambiencePath), inventory(inventory) {}

Location camp(
    "camp",
    "I woke up sore, that familiar ache of winter mornings felt "
    "once again.\n\nExit: North",
    ":/images/camp.png", "qrc:/audio/music/placeholder.mp3",
    "qrc:/audio/ambience/mountainWind.mp3",
    {{"ARROW", 3, 0, 0, "TOOLS", "NONE",
      "I could load it into my bow to hunt at a distance."},
     {"BOW", 1, 0, 0, "TOOLS", "ARROW",
      "If loaded with an arrow, it could be used for hunting."},
     {"FISHING ROD", 1, 0, 0, "TOOLS", "RENDERED FAT",
      "If loaded with bait such as rendered fat, I could catch fish with it."},
     {"LANTERN", 1, 0, 0, "TOOLS", "TALLOW CANDLE",
      "If loaded with a tallow candle, I could use it to light my way."}});

Location
    campPath("campPath",
             "I moved through a break in the trees for a while before "
             "reaching a fork in the road.\n\nExits: North, South, East, West",
             ":/images/campPath.png", "qrc:/audio/music/placeholder.mp3",
             "qrc:/audio/ambience/mountainWind.mp3",
             {{"PIECE OF WOOD", 1, 0, 0, "RESOURCES", "NONE",
               "I could use it to fuel my campfire or to craft items."}});

Location
    caveEntrance("caveEntrance",
                 "I happened upon a cave, it didn't seem like a good idea to "
                 "find out what it contained.\n\nExits: West, East",
                 ":/images/caveEntrance.png",
                 "qrc:/audio/music/placeholder.mp3",
                 "qrc:/audio/ambience/mountainWind.mp3",
                 {{"ROCK", 1, 0, 0, "TOOLS", "NONE",
                   "I could use it to distract animals."}});

Location cave("cave",
              "Entering the cave, I saw nothing but darkness.\n\nExit: West",
              ":/images/cave.png", "qrc:/audio/music/placeholder.mp3",
              "qrc:/audio/ambience/mountainWind.mp3",
              {{"ROCK", 1, 0, 0, "TOOLS", "NONE",
                "I could use it to distract animals."}});

Location caveLit("caveLit", "My lantern now lit the way.\n\nExit: West",
                 ":/images/caveLit.png", "qrc:/audio/music/placeholder.mp3",
                 "qrc:/audio/ambience/mountainWind.mp3",
                 {{"ROCK", 1, 0, 0, "TOOLS", "NONE",
                   "I could use it to distract animals."}});

Location intro("intro",
               "HALFWAY ACROSS\n\nType BEGIN to continue.\nType HELP for a "
               "list of commands.",
               ":/images/intro.png", "qrc:/audio/music/placeholder.mp3",
               "qrc:/audio/ambience/mountainWind.mp3", {{}});

Location lake("lake",
              "I arrived at a lake after an hour's journey.\n\nExit: East",
              ":/images/lake.png", "qrc:/audio/music/placeholder.mp3",
              "qrc:/audio/ambience/mountainWind.mp3",
              {{"CHISEL", 1, 0, 0, "TOOLS", "NONE",
                "I could use it to break through ice."}});

Location perished("perished", "\n\nType QUIT to exit.", ":/images/perished.png",
                  "qrc:/audio/music/placeholder.mp3",
                  "qrc:/audio/ambience/mountainWind.mp3", {{{}}});

Location valley("valley",
                "I arrived at a clearing. It seemed like a good spot for "
                "hunting.\n\nExit: South",
                ":/images/valley.png", "qrc:/audio/music/placeholder.mp3",
                "qrc:/audio/ambience/mountainWind.mp3",
                {{"FEATHER", 3, 0, 0, "RESOURCES", "NONE",
                  "I could use it for crafting."}});

QString Location::getName() const { return name; }
QString Location::getDescription() const { return description; }
QString Location::getImage() const { return image; }
QString Location::getAmbiencePath() const { return ambiencePath; }
QString Location::getMusicPath() const { return musicPath; }
QString Location::setDescription(QString message) {
  description = message + description;
  return description;
}

std::vector<Item> &Location::getInventory() { return inventory; }

QString Location::locInventory() const {
  QString inventoryText;
  for (const auto &item : inventory) {
    inventoryText.append(
        QString("%1: %2\n").arg(item.getName()).arg(item.getAmount()));
  }
  if (inventoryText != "") {
    inventoryText.prepend("Looking at the ground, I saw:\n");
  } else {
    inventoryText.append("I didn't see anything of note on the ground.");
  }
  return inventoryText;
}

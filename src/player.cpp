#include "../include/player.h"
#include "../include/world.h"
#include <qdebug.h>

#define LOW_STAT_THRESHOLD 30
#define MEDIUM_STAT_THRESHOLD 50
#define HIGH_STAT_THRESHOLD 70

Player player;

Player::Player()
    : health(100), mental(50), energy(1), hunger(100), thirst(100), warmth(50),
      charm(50), standing(1), inventory(5), recipeBook(2) {
  // Format is QString name, int amount, int active, int effects, QString type
  inventory.push_back({"FELT HAT", 1, 1, 5, "CLOTHING", "NONE"});
  inventory.push_back({"LEATHER GLOVES", 1, 1, 5, "CLOTHING", "NONE"});
  inventory.push_back({"HEAVY COTTON SHIRT", 1, 1, 10, "CLOTHING", "NONE"});
  inventory.push_back({"HEAVY COTTON TROUSERS", 1, 1, 20, "CLOTHING", "NONE"});
  inventory.push_back({"PAIR OF MOCCASINS", 1, 1, 10, "CLOTHING", "NONE"});
  Recipe candle("TALLOW CANDLE", "RENDERED FAT", "PIECE OF WOOD",
                {"TALLOW CANDLE", 1, 1, 10, "ANIMAL FAT", "NONE"});
  recipeBook.push_back(candle);
}

int Player::getHealth() const { return health; }
int Player::setHealth(int h) {
  health = constrainStat(h);
  if (health == 0) {
    return 1;
  } else {
    return 0;
  }
}

int Player::getMental() const { return mental; }
int Player::setMental(int m) {
  mental = constrainStat(m);
  if (mental == 0) {
    return 1;
  } else {
    return 0;
  }
}

int Player::getEnergy() const { return energy; }
void Player::setEnergy(int e) { energy = constrainStat(e); }

int Player::getHunger() const { return hunger; }
int Player::setHunger(int h) {
  hunger = constrainStat(h);
  if (hunger == 0) {
    return 1;
  } else {
    return 0;
  }
}

int Player::getThirst() const { return thirst; }
int Player::setThirst(int t) {
  thirst = constrainStat(t);
  if (thirst == 0) {
    return 1;
  } else {
    return 0;
  }
}

int Player::getWarmth() const { return warmth; }
int Player::setWarmth(int w) {
  warmth = constrainStat(w);
  if (warmth == 0) {
    return 1;
  } else {
    return 0;
  }
}

int Player::getCharm() const { return charm; }
void Player::setCharm(int c) { charm = constrainStat(c); }

int Player::getStanding() const { return standing; }
void Player::setStanding(int s) { standing = constrainStat(s); }

std::vector<Item> &Player::getInventory() { return inventory; }

std::vector<Recipe> &Player::getRecipeBook() { return recipeBook; }

int Player::constrainStat(int stat) { return std::max(0, std::min(stat, 100)); }

// Warning messages were opted for over showing the player the associated ints
// for the sake of realism
QString Player::constructReflection() const {
  QString reflection;
  reflection.append(QString("Day %1\n").arg(world.getDay()));

  if (warmth < LOW_STAT_THRESHOLD) {
    reflection.append("I didn't think I could survive the cold much longer.\n");
  } else if (LOW_STAT_THRESHOLD <= warmth && warmth < MEDIUM_STAT_THRESHOLD) {
    reflection.append("The cold was becoming unbearable.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= warmth && warmth < HIGH_STAT_THRESHOLD) {
    reflection.append("The cold was starting to get to me.\n");
  }

  if (health < LOW_STAT_THRESHOLD) {
    reflection.append("My health was deteriorating quickly.\n");
  } else if (LOW_STAT_THRESHOLD <= health && health < MEDIUM_STAT_THRESHOLD) {
    reflection.append("I felt very ill.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= health && health < HIGH_STAT_THRESHOLD) {
    reflection.append("I felt a little under the weather.\n");
  }

  if (hunger < LOW_STAT_THRESHOLD) {
    reflection.append("I was starving.\n");
  } else if (LOW_STAT_THRESHOLD <= hunger && hunger < MEDIUM_STAT_THRESHOLD) {
    reflection.append("I needed to eat something soon.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= hunger && hunger < HIGH_STAT_THRESHOLD) {
    reflection.append("I was starting to get hungry.\n");
  }

  if (thirst < LOW_STAT_THRESHOLD) {
    reflection.append("My throat was very dry.\n");
  } else if (LOW_STAT_THRESHOLD <= thirst && thirst < MEDIUM_STAT_THRESHOLD) {
    reflection.append("I needed to drink something soon.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= thirst && thirst < HIGH_STAT_THRESHOLD) {
    reflection.append("I was starting to get thirsty.\n");
  }
  return reflection;
}

// Limits on how many of each type of clothing item can be equipped at once will
// be implemented in the future
QString Player::clothesInventory() {
  QString inventoryText;
  for (const auto &item : inventory) {
    if (item.getType() == "CLOTHING" && item.getActive() == 1) {
      inventoryText.append(QString("%1\n").arg(item.getName()));
    }
  }
  if (inventoryText != "") {
    inventoryText.prepend("I was wearing:\n");
  } else {
    inventoryText.append("I was not wearing anything.");
  }
  return inventoryText;
}

// The space inside the player's inventory will likely be limited in the future
QString Player::bagInventory() {
  QString inventoryText;
  for (const auto &item : inventory) {
    if (item.getType() != "CLOTHING" && item.getType() != "") {
      inventoryText.append(
          QString("%1: %2\n").arg(item.getName()).arg(item.getAmount()));
    }
  }
  if (inventoryText != "") {
    inventoryText.prepend("Looking in my possibles bag, I saw:\n");
  } else {
    inventoryText.append("My possibles bag was empty.");
  }
  return inventoryText;
}

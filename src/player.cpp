#include "../include/player.h"
#include "../include/world.h"

#define LOW_STAT_THRESHOLD 20
#define MEDIUM_STAT_THRESHOLD 50
#define HIGH_STAT_THRESHOLD 70

playerStats player;

playerStats::playerStats()
    : health(100), energy(1), hunger(100), thirst(100), warmth(50), charm(50),
      standing(1), inventory(5) {
  // Format is QString name, int amount, int active, int effects, QString type
  inventory.push_back({"FELT HAT", 1, 1, 5, "clothing"});
  inventory.push_back({"LEATHER GLOVES", 1, 1, 5, "clothing"});
  inventory.push_back({"HEAVY COTTON SHIRT", 1, 1, 10, "clothing"});
  inventory.push_back({"HEAVY COTTON TROUSERS", 1, 1, 20, "clothing"});
  inventory.push_back({"MOCCASINS", 1, 1, 10, "clothing"});
}

int playerStats::getHealth() const { return health; }
void playerStats::setHealth(int h) { health = constrainStat(h); }

int playerStats::getEnergy() const { return energy; }
void playerStats::setEnergy(int e) { energy = constrainStat(e); }

int playerStats::getHunger() const { return hunger; }
void playerStats::setHunger(int h) { hunger = constrainStat(h); }

int playerStats::getThirst() const { return thirst; }
void playerStats::setThirst(int t) { thirst = constrainStat(t); }

int playerStats::getWarmth() const { return warmth; }
void playerStats::setWarmth(int w) { warmth = constrainStat(w); }

int playerStats::getCharm() const { return charm; }
void playerStats::setCharm(int c) { charm = constrainStat(c); }

int playerStats::getStanding() const { return standing; }
void playerStats::setStanding(int s) { standing = constrainStat(s); }

std::vector<item> &playerStats::getInventory() { return inventory; }

int playerStats::constrainStat(int stat) {
  return std::max(0, std::min(stat, 100));
}

QString playerStats::constructReflection() const {
  QString reflection;
  reflection.append(
      QString("Day %1 in the San Juan mountains.\n").arg(world.getDay()));

  if (player.warmth < LOW_STAT_THRESHOLD) {
    reflection.append("You won't survive this cold much longer.\n");
  } else if (LOW_STAT_THRESHOLD <= player.warmth &&
             player.warmth < MEDIUM_STAT_THRESHOLD) {
    reflection.append("The cold is becoming unbearable.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= player.warmth &&
             player.warmth < HIGH_STAT_THRESHOLD) {
    reflection.append("The cold is starting to get to you.\n");
  }

  if (player.health < LOW_STAT_THRESHOLD) {
    reflection.append("Your health is deteriorating quickly.\n");
  } else if (LOW_STAT_THRESHOLD <= player.health &&
             player.health < MEDIUM_STAT_THRESHOLD) {
    reflection.append("You feel very ill.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= player.health &&
             player.health < HIGH_STAT_THRESHOLD) {
    reflection.append("You feel a little under the weather.\n");
  }

  if (player.hunger < LOW_STAT_THRESHOLD) {
    reflection.append("You are starving.\n");
  } else if (LOW_STAT_THRESHOLD <= player.hunger &&
             player.hunger < MEDIUM_STAT_THRESHOLD) {
    reflection.append("You need to eat something soon.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= player.hunger &&
             player.hunger < HIGH_STAT_THRESHOLD) {
    reflection.append("You are starting to get hungry.\n");
  }

  if (player.thirst < LOW_STAT_THRESHOLD) {
    reflection.append("Your throat is very dry.\n");
  } else if (LOW_STAT_THRESHOLD <= player.thirst &&
             player.thirst < MEDIUM_STAT_THRESHOLD) {
    reflection.append("You need to drink something soon.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= player.thirst &&
             player.thirst < HIGH_STAT_THRESHOLD) {
    reflection.append("You are starting to get thirsty.\n");
  }
  return reflection;
}

QString playerStats::clothesInventory() {
  QString inventoryText;
  for (const auto &item : inventory) {
    if (item.type == "clothing" && item.active == 1) {
      inventoryText.append(QString("%1\n").arg(item.name));
    }
  }
  if (inventoryText != "") {
      inventoryText.prepend("You are wearing:\n");
  }
  else {
      inventoryText.append("You are not wearing anything.");
  }
  return inventoryText;
}

QString playerStats::bagInventory() {
  QString inventoryText;
  for (const auto &item : inventory) {
    if (item.type != "clothing" && item.type != "") {
      inventoryText.append(QString("%1: %2\n").arg(item.name).arg(item.amount));
    }
  }
  if (inventoryText != "") {
  inventoryText.prepend("You have:\n");
  }
  else {
      inventoryText.append("Your possibles bag is empty.");
  }
  return inventoryText;
}


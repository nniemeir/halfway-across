#include "../include/player.h"
#include "../include/world.h"

#define LOW_STAT_THRESHOLD 20
#define MEDIUM_STAT_THRESHOLD 50
#define HIGH_STAT_THRESHOLD 70

Player player;

Player::Player()
    : health(100), energy(1), hunger(100), thirst(100), warmth(50), charm(50),
      standing(1), inventory(5) {
  // Format is QString name, int amount, int active, int effects, QString type
  inventory.push_back({"FELT HAT", 1, 1, 5, "clothing"});
  inventory.push_back({"LEATHER GLOVES", 1, 1, 5, "clothing"});
  inventory.push_back({"HEAVY COTTON SHIRT", 1, 1, 10, "clothing"});
  inventory.push_back({"HEAVY COTTON TROUSERS", 1, 1, 20, "clothing"});
  inventory.push_back({"MOCCASINS", 1, 1, 10, "clothing"});
}

int Player::getHealth() const { return health; }
void Player::setHealth(int h) { health = constrainStat(h); }

int Player::getEnergy() const { return energy; }
void Player::setEnergy(int e) { energy = constrainStat(e); }

int Player::getHunger() const { return hunger; }
void Player::setHunger(int h) { hunger = constrainStat(h); }

int Player::getThirst() const { return thirst; }
void Player::setThirst(int t) { thirst = constrainStat(t); }

int Player::getWarmth() const { return warmth; }
void Player::setWarmth(int w) { warmth = constrainStat(w); }

int Player::getCharm() const { return charm; }
void Player::setCharm(int c) { charm = constrainStat(c); }

int Player::getStanding() const { return standing; }
void Player::setStanding(int s) { standing = constrainStat(s); }

std::vector<item> &Player::getInventory() { return inventory; }

int Player::constrainStat(int stat) {
  return std::max(0, std::min(stat, 100));
}

// Warning messages were opted for over showing the player the associated ints for the sake of realism
QString Player::constructReflection() const {
  QString reflection;
  reflection.append(
      QString("Day %1 in the San Juan mountains.\n").arg(world.getDay()));

  if (warmth < LOW_STAT_THRESHOLD) {
    reflection.append("You won't survive this cold much longer.\n");
  } else if (LOW_STAT_THRESHOLD <= warmth &&
             warmth < MEDIUM_STAT_THRESHOLD) {
    reflection.append("The cold is becoming unbearable.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= warmth &&
             warmth < HIGH_STAT_THRESHOLD) {
    reflection.append("The cold is starting to get to you.\n");
  }

  if (health < LOW_STAT_THRESHOLD) {
    reflection.append("Your health is deteriorating quickly.\n");
  } else if (LOW_STAT_THRESHOLD <= health &&
             health < MEDIUM_STAT_THRESHOLD) {
    reflection.append("You feel very ill.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= health &&
             health < HIGH_STAT_THRESHOLD) {
    reflection.append("You feel a little under the weather.\n");
  }

  if (hunger < LOW_STAT_THRESHOLD) {
    reflection.append("You are starving.\n");
  } else if (LOW_STAT_THRESHOLD <= hunger &&
             hunger < MEDIUM_STAT_THRESHOLD) {
    reflection.append("You need to eat something soon.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= hunger &&
             hunger < HIGH_STAT_THRESHOLD) {
    reflection.append("You are starting to get hungry.\n");
  }

  if (thirst < LOW_STAT_THRESHOLD) {
    reflection.append("Your throat is very dry.\n");
  } else if (LOW_STAT_THRESHOLD <= thirst &&
             thirst < MEDIUM_STAT_THRESHOLD) {
    reflection.append("You need to drink something soon.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= thirst &&
             thirst < HIGH_STAT_THRESHOLD) {
    reflection.append("You are starting to get thirsty.\n");
  }
  return reflection;
}

// Limits on how many of each type of clothing item can be equipped at once will be implemented in the future
QString Player::clothesInventory() {
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

// The space inside the player's inventory will likely be limited in the future
QString Player::bagInventory() {
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


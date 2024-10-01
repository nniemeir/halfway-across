#include "../include/player.h"
#include "../include/world.h"

#define LOW_STAT_THRESHOLD 30
#define MEDIUM_STAT_THRESHOLD 50
#define HIGH_STAT_THRESHOLD 70

Player playerObj;

Player::Player()
    : health(100), mental(50), energy(1), hunger(100), thirst(100), warmth(50),
      charm(50), standing(1), cryCooldown(0), inventory(5), recipeBook(2) {
  // Format is QString name, int amount, int active, int effects, int weight,
  // QString type, QString description
  inventory.push_back({"FELT HAT", 1, 1, 5, 0, "CLOTHING", "NONE",
                       "It was a small hat, providing almost no warmth."});
  inventory.push_back({"LEATHER GLOVES", 1, 1, 5, 0, "CLOTHING", "NONE",
                       "They were thin gloves, providing almost no warmth."});
  inventory.push_back({"HEAVY COTTON SHIRT", 1, 1, 10, 0, "CLOTHING", "NONE",
                       "It was a heavy shirt, providing slight warmth."});
  inventory.push_back({"HEAVY COTTON TROUSERS", 1, 1, 20, 0, "CLOTHING", "NONE",
                       "They were thick pants, providing warmth."});
  inventory.push_back({"PAIR OF MOCCASINS", 1, 1, 10, 0, "CLOTHING", "NONE",
                       "They were worn shoes, providing slight warmth."});
  Recipe candle("TALLOW CANDLE", {"RENDERED FAT", "PIECE OF WOOD"},
                "Used to fuel candle lanterns.",
                {"TALLOW CANDLE", 1, 1, 10, 0, "ANIMAL FAT", "NONE",
                 "I could use it to fuel my lantern."});
  Recipe arrow("ARROW", {"ROCK", "PIECE OF WOOD", "FEATHER"},
               "Could be loaded into a bow to hunt at a distance.",
               {"ARROW", 1, 0, 0, 0, "TOOLS", "NONE",
                "I could load it into my bow to hunt at a distance."});
  recipeBook.push_back(arrow);
  recipeBook.push_back(candle);
}

int Player::getHealth() const { return health; }
int Player::getMental() const { return mental; }
int Player::getEnergy() const { return energy; }
int Player::getHunger() const { return hunger; }
int Player::getThirst() const { return thirst; }
int Player::getWarmth() const { return warmth; }
int Player::getCharm() const { return charm; }
int Player::getStanding() const { return standing; }
int Player::getCryCooldown() const { return cryCooldown; }
std::vector<Item> &Player::getInventory() { return inventory; }
std::vector<Recipe> &Player::getRecipeBook() { return recipeBook; }

int Player::setHealth(int h) {
  health = constrainStat(h);
  if (health == 0) {
    return 1;
  } else {
    return 0;
  }
}

int Player::setMental(int m) {
  mental = constrainStat(m);
  if (mental == 0) {
    return 1;
  } else {
    return 0;
  }
}

void Player::setEnergy(int e) { energy = constrainStat(e); }

int Player::setHunger(int h) {
  hunger = constrainStat(h);
  if (hunger == 0) {
    return 1;
  } else {
    return 0;
  }
}

int Player::setThirst(int t) {
  thirst = constrainStat(t);
  if (thirst == 0) {
    return 1;
  } else {
    return 0;
  }
}

int Player::setWarmth(int w) {
  warmth = constrainStat(w);
  if (warmth == 0) {
    return 1;
  } else {
    return 0;
  }
}

void Player::setCharm(int c) { charm = constrainStat(c); }
void Player::setStanding(int s) { standing = constrainStat(s); }
void Player::setCryCooldown(int s) { cryCooldown = s; }
int Player::constrainStat(int stat) { return std::max(0, std::min(stat, 100)); }
QString Player::displayBagInventory() const {
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

// Limits on how many of each type of clothing item can be equipped at once will
// be implemented in the future
QString Player::displayClothesInventory() const {
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

QString Player::displayRecipeBook() const {
  QString inventoryText;
  for (const auto &recipe : recipeBook) {
    if (recipe.getRecipeName() != "") {
      inventoryText.append(
          QString("%1\nIngredients:\n").arg(recipe.getRecipeName()));
      for (const auto &ingredient : recipe.getIngredients()) {
        inventoryText.append(QString("   - %1\n").arg(ingredient));
      }
      inventoryText.append(
          QString("Description:\n%1\n\n").arg(recipe.getDescription()));
    }
  }
  return inventoryText;
}

QString Player::displayWarnings() const {
  QString warnings;
  warnings.append(QString("Day %1\n\n").arg(worldObj.getDay()));

  if (mental < LOW_STAT_THRESHOLD) {
    warnings.append("I was losing the will to continue. ");
  } else if (LOW_STAT_THRESHOLD <= mental && mental < MEDIUM_STAT_THRESHOLD) {
    warnings.append("My depression was worsening. ");
  } else if (MEDIUM_STAT_THRESHOLD <= mental && mental < HIGH_STAT_THRESHOLD) {
    warnings.append("I felt a bit melancholy. ");
  }

  if (warmth < LOW_STAT_THRESHOLD) {
    warnings.append("I didn't think I could survive the cold much longer. ");
  } else if (LOW_STAT_THRESHOLD <= warmth && warmth < MEDIUM_STAT_THRESHOLD) {
    warnings.append("The cold was becoming unbearable. ");
  } else if (MEDIUM_STAT_THRESHOLD <= warmth && warmth < HIGH_STAT_THRESHOLD) {
    warnings.append("The cold was starting to get to me. ");
  }

  if (health < LOW_STAT_THRESHOLD) {
    warnings.append("My health was deteriorating quickly. ");
  } else if (LOW_STAT_THRESHOLD <= health && health < MEDIUM_STAT_THRESHOLD) {
    warnings.append("I felt very ill. ");
  } else if (MEDIUM_STAT_THRESHOLD <= health && health < HIGH_STAT_THRESHOLD) {
    warnings.append("I felt a little under the weather. ");
  }

  if (hunger < LOW_STAT_THRESHOLD) {
    warnings.append("I was starving. ");
  } else if (LOW_STAT_THRESHOLD <= hunger && hunger < MEDIUM_STAT_THRESHOLD) {
    warnings.append("I needed to eat something soon. ");
  } else if (MEDIUM_STAT_THRESHOLD <= hunger && hunger < HIGH_STAT_THRESHOLD) {
    warnings.append("I was starting to get hungry. ");
  }

  if (thirst < LOW_STAT_THRESHOLD) {
    warnings.append("My throat was very dry. ");
  } else if (LOW_STAT_THRESHOLD <= thirst && thirst < MEDIUM_STAT_THRESHOLD) {
    warnings.append("I needed to drink something soon. ");
  } else if (MEDIUM_STAT_THRESHOLD <= thirst && thirst < HIGH_STAT_THRESHOLD) {
    warnings.append("I was starting to get thirsty. ");
  }
  return warnings;
}
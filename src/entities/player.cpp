#include "../../include/entities/player.h"
#include "../../include/core/world.h"

Player::Player()
    : health(100), mental(50), energized(true), hunger(100), thirst(100),
      warmth(50), charm(50), standing(true), cryCooldown(0), inventory(5),
      recipeBook(2) {
  inventory.push_back({"FELT HAT",
                       "It was a small hat, providing almost no warmth.",
                       "CLOTHING", "NONE", 1, true, 5, 0});
  inventory.push_back({"LEATHER GLOVES",
                       "They were thin gloves, providing almost no warmth.",
                       "CLOTHING", "NONE", 1, true, 5, 0});
  inventory.push_back({"HEAVY COTTON SHIRT",
                       "It was a heavy shirt, providing slight warmth.",
                       "CLOTHING", "NONE", 1, true, 10, 0});
  inventory.push_back({"HEAVY COTTON TROUSERS",
                       "They were thick pants, providing warmth.", "CLOTHING",
                       "NONE", 1, true, 20, 0});
  inventory.push_back({"PAIR OF MOCCASINS",
                       "They were worn shoes, providing slight warmth.",
                       "CLOTHING", "NONE", 1, true, 10, 0});
  Recipe arrow("ARROW", "Could be loaded into a bow to hunt at a distance.",
               {"ROCK", "PIECE OF WOOD", "FEATHER"},
               {"ARROW", "I could load it into my bow to hunt at a distance.",
                "TOOLS", "NONE", 1, false, 0, 0});
  Recipe candle("TALLOW CANDLE", "Used to fuel candle lanterns.",
                {"RENDERED FAT", "PIECE OF WOOD"},
                {"TALLOW CANDLE", "I could use it to fuel my lantern.",
                 "ANIMAL FAT", "NONE", 1, false, 10, 0});
  recipeBook.push_back(arrow);
  recipeBook.push_back(candle);
}

int Player::getHealth() const { return health; }

int Player::getMental() const { return mental; }

bool Player::getEnergized() const { return energized; }

int Player::getHunger() const { return hunger; }

int Player::getThirst() const { return thirst; }

int Player::getWarmth() const { return warmth; }

int Player::getCharm() const { return charm; }

bool Player::getStanding() const { return standing; }

int Player::getCryCooldown() const { return cryCooldown; }

std::vector<Item> &Player::getInventory() { return inventory; }

std::vector<Recipe> &Player::getRecipeBook() { return recipeBook; }

// A stat change returning false indicates a game over condition
bool Player::setHealth(int h) {
  health = constrainStat(h);
  if (health != 0) {
    return true;
  }
  return false;
}

bool Player::setMental(int m) {
  mental = constrainStat(m);
  if (mental != 0) {
    return true;
  }
  return false;
}

void Player::setEnergized(bool e) { energized = constrainStat(e); }

bool Player::setHunger(int h) {
  hunger = constrainStat(h);
  if (hunger != 0) {
    return true;
  }
  return false;
}

bool Player::setThirst(int t) {
  thirst = constrainStat(t);
  if (thirst != 0) {
    return true;
  }
  return false;
}

bool Player::setWarmth(int w) {
  warmth = constrainStat(w);
  if (warmth != 0) {
    return true;
  }
  return false;
}

void Player::setCharm(int c) { charm = constrainStat(c); }

void Player::setStanding(bool s) { standing = constrainStat(s); }

void Player::setCryCooldown(int s) { cryCooldown = s; }

int Player::constrainStat(int stat) { return std::max(0, std::min(stat, 100)); }

QString Player::displayBagInventory() const {
  QStringList inventoryItemsText;
  for (const auto &item : inventory) {
    if (item.getType() != "CLOTHING" && !item.getType().isEmpty()) {
      inventoryItemsText.append(
          QString("%1: %2").arg(item.getName()).arg(item.getAmount()));
    }
  }
  std::sort(inventoryItemsText.begin(), inventoryItemsText.end());
  QString inventoryText;
  if (inventoryItemsText.isEmpty()) {
    inventoryText.append("My possibles bag was empty.");
    return inventoryText;
  }
  inventoryText.append("Looking in my possibles bag, I saw:\n");
  inventoryText.append(inventoryItemsText.join("\n"));
  return inventoryText;
}

// Limits on how many of each type of clothing item can be equipped at once will
// be implemented in the future
QString Player::displayClothesInventory() const {
  QStringList inventoryItemsText;
  for (const auto &item : inventory) {
    if (item.getType() == "CLOTHING" && item.getActive()) {
      inventoryItemsText.append(item.getName());
    }
  }
  std::sort(inventoryItemsText.begin(), inventoryItemsText.end());
  QString inventoryText;
  if (inventoryItemsText.isEmpty()) {
    inventoryText.append("I was not wearing anything.");
    return inventoryText;
  }
  inventoryText.append("I was wearing:\n");
  inventoryText.append(inventoryItemsText.join("\n"));
  return inventoryText;
}

// The contents of a given day's journal entry will differ in later versions
// based on player actions and stats
QString Player::displayJournal() const {
  QString entry;
  entry.append(QString("Day %1\n\n").arg(worldObj.getDay()));
  QMap<int, QString> dayEntries = {
      {1, "I finished setting up camp this morning, its not exactly "
          "comfortable but it will have to do for now. I still have some "
          "rations from the journey here, but I would be wise to hunt soon. I "
          "could use the command LOOK AROUND to survey my surroundings."},
      {2, "I want for little but seclusion, to disconnect from everything that "
          "has become so alien to me."}};

  if (dayEntries.contains(worldObj.getDay())) {
    entry.append(dayEntries.value(worldObj.getDay()));
    return entry;
  }
  entry.append("A normal day in the mountains.");
  return entry;
}

QString Player::displayRecipeBook() const {
  QString inventoryText;
  for (const auto &recipe : recipeBook) {
    if (!recipe.getRecipeName().isEmpty()) {
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

QString Player::generateWarnings() const {
  QString warnings;
  warnings.append(
      QString("It was %1 today. ").arg(worldObj.getCurrentWeather()));
  if (mental < STAT_LOW_THRESHOLD) {
    warnings.append("I was losing the will to continue. ");
  } else if (STAT_LOW_THRESHOLD <= mental && mental < STAT_MEDIUM_THRESHOLD) {
    warnings.append("My depression was worsening. ");
  } else if (STAT_MEDIUM_THRESHOLD <= mental && mental < STAT_HIGH_THRESHOLD) {
    warnings.append("I felt a bit melancholy. ");
  }

  QString warmthWarning = generateWarmthWarning();
  if (!warmthWarning.isEmpty()) {
    warnings.append(warmthWarning);
  }

  if (health < STAT_LOW_THRESHOLD) {
    warnings.append("My health was deteriorating quickly. ");
  } else if (STAT_LOW_THRESHOLD <= health && health < STAT_MEDIUM_THRESHOLD) {
    warnings.append("I felt very ill. ");
  } else if (STAT_MEDIUM_THRESHOLD <= health && health < STAT_HIGH_THRESHOLD) {
    warnings.append("I felt a little under the weather. ");
  }

  if (hunger < STAT_LOW_THRESHOLD) {
    warnings.append("I was starving. ");
  } else if (STAT_LOW_THRESHOLD <= hunger && hunger < STAT_MEDIUM_THRESHOLD) {
    warnings.append("I needed to eat something soon. ");
  } else if (STAT_MEDIUM_THRESHOLD <= hunger && hunger < STAT_HIGH_THRESHOLD) {
    warnings.append("I was starting to get hungry. ");
  }

  if (thirst < STAT_LOW_THRESHOLD) {
    warnings.append("My throat was very dry. ");
  } else if (STAT_LOW_THRESHOLD <= thirst && thirst < STAT_MEDIUM_THRESHOLD) {
    warnings.append("I needed to drink something soon. ");
  } else if (STAT_MEDIUM_THRESHOLD <= thirst && thirst < STAT_HIGH_THRESHOLD) {
    warnings.append("I was starting to get thirsty. ");
  }
  return warnings;
}

QString Player::generateWarmthWarning() const {
  int currentTemperature = worldObj.getCurrentTemperature();
  QString warning;
  QString BStatMsg = "I felt a bit cold. ";
  QString CStatMsg = "The cold was starting to get to me. ";
  QString DStatMsg = "The cold was becoming unbearable. ";
  QString FStatMsg =
      "I didn't think that I could survive the cold much longer. ";

  if (currentTemperature < 5) {
    if (warmth < 25) {
      warning = FStatMsg;
    } else if (warmth < 50) {
      warning = DStatMsg;

    } else if (warmth < 75) {
      warning = CStatMsg;
    } else {
      warning = BStatMsg;
    }
  } else if (currentTemperature < 10) {
    if (warmth < 50) {
      warning = DStatMsg;
    } else if (warmth < 75) {
      warning = CStatMsg;
    } else {
      warning = BStatMsg;
    }
  } else if (currentTemperature < 15) {
    if (warmth < 25) {
      warning = DStatMsg;
    } else if (warmth < 50) {
      warning = CStatMsg;
    } else if (warmth < 75) {
      warning = BStatMsg;
    }
  } else if (currentTemperature < 20) {
    if (warmth < 25) {
      warning = CStatMsg;
    } else if (warmth < 50) {
      warning = BStatMsg;
    }
  }
  return warning;
}

Player playerObj;

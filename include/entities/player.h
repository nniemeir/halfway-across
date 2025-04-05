#ifndef PLAYER_H_
#define PLAYER_H_
#include "../../include/items/inventory.h"
#include "../../include/items/item.h"
#include "../../include/items/recipe.h"
#include <QMap>

// Contains attributes specific to the player
class Player : public Inventory {
public:
  Player();
  static constexpr int STAT_LOW_THRESHOLD = 30;
  static constexpr int STAT_MEDIUM_THRESHOLD = 50;
  static constexpr int STAT_HIGH_THRESHOLD = 70;
  int getHealth() const;
  int getMental() const;
  bool getEnergized() const;
  int getHunger() const;
  int getThirst() const;
  int getWarmth() const;
  int getCharm() const;
  bool getStanding() const;
  int getCryCooldown() const;
  std::vector<Item> &getInventory();
  std::vector<Recipe> &getRecipeBook();
  bool setHealth(int health);
  bool setMental(int mental);
  void setEnergized(bool energized);
  bool setHunger(int hunger);
  bool setThirst(int thirst);
  bool setWarmth(int warmth);
  void setCharm(int charm);
  void setStanding(bool standing);
  void setCryCooldown(int s);
  int constrainStat(int stat);
  QString displayBagInventory() const;
  QString displayClothesInventory() const;
  QString displayJournal() const;
  QString displayRecipeBook() const;
  QString generateWarnings() const;
  QString generateWarmthWarning() const;

private:
  int health;
  int mental;
  bool energized;
  int hunger;
  int thirst;
  int warmth;
  int charm;
  bool standing;
  int cryCooldown;
  std::vector<Item> inventory;
  std::vector<Recipe> recipeBook;
};

extern Player playerObj;

#endif

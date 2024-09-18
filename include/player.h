#ifndef PLAYER_H_
#define PLAYER_H_
#include "inventory.h"
#include "item.h"
#include "recipe.h"

class Player : public Inventory {
public:
  Player();

  // Stats management
  int getHealth() const;
  int setHealth(int health);
  int getMental() const;
  int setMental(int mental);
  int getEnergy() const;
  void setEnergy(int energy);
  int getHunger() const;
  int setHunger(int hunger);
  int getThirst() const;
  int setThirst(int thirst);
  int getWarmth() const;
  int setWarmth(int warmth);
  int getCharm() const;
  void setCharm(int charm);
  int getStanding() const;
  void setStanding(int standing);
  int constrainStat(int stat);
  QString constructReflection() const;

  // Inventory
  std::vector<Item> &getInventory();
  QString clothesInventory();
  QString bagInventory();
  std::vector<Recipe> &getRecipeBook();

private:
  int health;
  int mental;
  int energy;
  int hunger;
  int thirst;
  int warmth;
  int charm;
  int standing;
  std::vector<Item> inventory;
  std::vector<Recipe> recipeBook;
};

extern Player player;

#endif

#ifndef PLAYER_H_
#define PLAYER_H_
#include "inventory.h"
#include "item.h"
#include "recipe.h"
#include <QMap>

class Player : public Inventory {
public:
  Player();

  int getHealth() const;
  int getMental() const;
  int getEnergy() const;
  int getHunger() const;
  int getThirst() const;
  int getWarmth() const;
  int getCharm() const;
  int getStanding() const;
  int getCryCooldown() const;
  std::vector<Item> &getInventory();
  std::vector<Recipe> &getRecipeBook();
  int setHealth(int health);
  int setMental(int mental);
  void setEnergy(int energy);
  int setHunger(int hunger);
  int setThirst(int thirst);
  int setWarmth(int warmth);
  void setCharm(int charm);
  void setStanding(int standing);
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
  int energy;
  int hunger;
  int thirst;
  int warmth;
  int charm;
  int standing;
  int cryCooldown;
  std::vector<Item> inventory;
  std::vector<Recipe> recipeBook;
};

extern Player playerObj;

#endif

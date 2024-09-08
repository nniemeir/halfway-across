#ifndef PLAYER_H_
#define PLAYER_H_
#include "inventory.h"
#include "item.h"

class Player: public Inventory {
public:
  Player();

  // Stats management
  int getHealth() const;
  void setHealth(int health);
  int getEnergy() const;
  void setEnergy(int energy);
  int getHunger() const;
  void setHunger(int hunger);
  int getThirst() const;
  void setThirst(int thirst);
  int getWarmth() const;
  void setWarmth(int warmth);
  int getCharm() const;
  void setCharm(int charm);
  int getStanding() const;
  void setStanding(int standing);
  int constrainStat(int stat);
  QString constructReflection() const;

  // Inventory
  std::vector<item> &getInventory();
  QString clothesInventory();
  QString bagInventory();

private:
  int health;
  int energy;
  int hunger;
  int thirst;
  int warmth;
  int charm;
  int standing;
  std::vector<item> inventory;

};

extern Player player;

#endif

#ifndef FISHING_H
#define FISHING_H
#include "../../include/items/item.h"

class Fishing {
public:
  Fishing();
  int getDailyAttempts() const;
  std::vector<Item> &getInventory();
  QString rollforFish();
  QString seek();
  void resetDailyAttempts();

private:
  int dailyAttempts;
  std::vector<Item> fish;
};

extern Fishing fishingObj;

#endif

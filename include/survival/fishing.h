#ifndef FISHING_H
#define FISHING_H
#include "../../include/items/item.h"

class Fishing {
public:
  Fishing();
  int getDailyAttempts() const;
  std::vector<Item> &getInventory();
  QString seek();
  QString rollforFish();
  void resetDailyAttempts();

private:
  std::vector<Item> fish;
  int dailyAttempts;
};

extern Fishing fishingObj;

#endif // FISHING_H

#ifndef FISHING_H
#define FISHING_H
#include "../include/item.h"

class Fishing {
public:
  Fishing();
  std::vector<Item> &getFishInventory();
  QString activity(int rodIndex);
  QString generateFish();
  void resetDailyFished();

private:
  std::vector<Item> fish;
  int dailyFished;
};

extern Fishing fishingObj;

#endif // FISHING_H

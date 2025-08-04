#ifndef FISHING_H
#define FISHING_H
#include "items/item.h"

// Handles the logic for the fishing activity
class Fishing {
public:
  Fishing();
  
  // Getters
  int getDailyAttempts() const;
  std::vector<Item> &getInventory();
  
  // Setters
  void resetDailyAttempts();
  
  // Logic
  QString rollforFish();
  QString seek();

private:
  int dailyAttempts;
  std::vector<Item> fish;
};

extern Fishing fishingObj;

#endif

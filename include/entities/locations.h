#ifndef LOCATIONS_H
#define LOCATIONS_H
#include "../../include/items/inventory.h"
#include "../../include/items/item.h"

class Location : public Inventory {
public:
  Location();
  Location(const QString &name, const QString &description,
           const QString &compassPath, const QString &imagePath,
           const QString &musicPath, const QString &ambiencePath,
           const std::vector<Item> &inventory);

  QString getName() const;
  QString getDescription() const;
  QString getCompassPath() const;
  QString getImagePath() const;
  QString getAmbiencePath() const;
  QString getMusicPath() const;
  QString setDescription(QString message);
  std::vector<Item> &getInventory();
  QString displayItems() const;

private:
  QString name;
  QString description;
  QString compassPath;
  QString imagePath;
  QString musicPath;
  QString ambiencePath;
  std::vector<Item> inventory;
};

extern Location camp;
extern Location forestPath;
extern Location cave;
extern Location caveEntrance;
extern Location caveLit;
extern Location intro;
extern Location lake;
extern Location perished;
extern Location valley;

#endif

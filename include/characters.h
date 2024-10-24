#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "item.h"

class Character {
public:
  Character(){};
  Character(const QString &n, const QString &d, const QString &l, const int &f,
            const bool &h, const int &t, const int &da, std::vector<Item> &i)
      : name(n), description(d), location(l), frequency(f), hatesPlayer(h),
        timesEncountered(t), daysSinceEncountered(da), inventory(i) {}

  QString getName() const;
  QString getDescription() const;
  QString getLocation() const;
  bool getDaysSinceEncountered() const;
  ;
  bool getFrequency() const;
  bool getHatesPlayer() const;
  std::vector<Item> &getInventory();
  void setDescription(QString newDescription);
  void setDaysSinceEncountered(int newDaysSince);
  void setFrequency(int newFrequency);
  void setHatesPlayer(bool newHatesPlayer);

private:
  QString name;
  QString description;
  QString location;
  int frequency;
  bool hatesPlayer;
  int timesEncountered;
  int daysSinceEncountered;
  std::vector<Item> inventory;
};

extern Character amos;
extern Character ira;

class Ensemble {
public:
  Ensemble();
  Character *getCharacter(int index);
  int searchEnsemble(const QString &itemName) const;
  std::vector<Character> &getCharacters();
  bool isCharacterName(QString target);

private:
  std::vector<Character> characters;
};

extern Ensemble ensembleObj;

#endif

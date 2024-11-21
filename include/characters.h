#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "item.h"

class Character {
public:
  Character(){};
  Character(const QString &n, const QString &d, const QString &b,
            const QString &im, const QString &l, const int &f, const bool &h,
            const int &r, const int &t, const int &da, const int &es,
            std::vector<Item> &i)
      : name(n), description(d), brief(b), image(im), location(l), frequency(f),
        hatesPlayer(h), reputation(r), timesEncountered(t),
        daysSinceEncountered(da), encounterState(es), inventory(i) {}

  QString getName() const;
  QString getDescription() const;
  QString getBrief() const;
  QString getImage() const;
  QString getLocation() const;
  int getTimesEncountered() const;
  int getDaysSinceEncountered() const;
  int getEncounterState() const;
  int getFrequency() const;
  bool getHatesPlayer() const;
  int getReputation() const;
  std::vector<Item> &getInventory();
  void setDescription(QString newDescription);
  void setDaysSinceEncountered(int newDaysSince);
  void incrementTimesEncountered();
  void setEncounterState(int newState);
  void setFrequency(int newFrequency);
  void setHatesPlayer(bool newHatesPlayer);
  void setReputation(int newReputation);

private:
  QString name;
  QString description;
  QString brief;
  QString image;
  QString location;
  int frequency;
  bool hatesPlayer;
  int reputation;
  int timesEncountered;
  int daysSinceEncountered;
  int encounterState;
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

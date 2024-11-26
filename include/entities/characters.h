#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "../../include/items/item.h"
#include <QMap>

class Character {
public:
  Character(){};
  Character(const QString &n, const QString &d, const QString &ub,
            const QString &b, const QString &im, const QString &l, const int &f,
            const bool &h, const int &r, const int &t, const int &da,
            const int &es, std::vector<Item> &i, const QMap<int, QString> &gm)
      : name(n), description(d), unknownBrief(ub), knownBrief(b), image(im),
        location(l), frequency(f), hatesPlayer(h), reputation(r),
        timesEncountered(t), daysSinceEncountered(da), encounterState(es),
        inventory(i), greetingMsgs(gm) {}

  QString getName() const;
  QString getDescription() const;
  QString getUnknownBrief() const;
  QString getKnownBrief() const;
  QString getImage() const;
  QString getLocation() const;
  QMap<int, QString> &getGreetingMsgs();
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
  QString unknownBrief;
  QString knownBrief;
  QString image;
  QString location;
  QMap<int, QString> greetingMsgs;
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
  static constexpr int AMOS_INDEX = 0;
  static constexpr int IRA_INDEX = 1;
  Character *getCharacter(int index);
  int searchEnsemble(const QString &itemName) const;
  std::vector<Character> &getCharacters();
  bool isCharacterName(QString target);

private:
  std::vector<Character> characters;
};

extern Ensemble ensembleObj;

#endif

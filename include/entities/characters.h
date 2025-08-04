#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "items/item.h"
#include <QMap>

// Contains attributes for human NPCs
class Character {
public:
  Character(){};
  Character(const QString &n, const QString &d, const QString &ub,
            const QString &b, const QString &im, const QString &l, const int &f,
            const bool &h, const int &r, const int &t, const int &da,
            const int &es, std::vector<Item> &i, const QMap<int, QString> &gm)
      : name(n), description(d), briefKnown(b), briefUnknown(ub), imagePath(im),
        location(l), frequency(f), hatesPlayer(h), reputation(r),
        daysSinceEncountered(da), timesEncountered(t), encounterState(es),
        greetingMsgs(gm), inventory(i) {}

  // Getters
  QString getName() const;
  QString getDescription() const;
  QString getBriefKnown() const;
  QString getBriefUnknown() const;
  QString getImagePath() const;
  QString getLocation() const;
  int getFrequency() const;
  bool getHatesPlayer() const;
  int getReputation() const;
  int getTimesEncountered() const;
  int getDaysSinceEncountered() const;
  int getEncounterState() const;
  QMap<int, QString> &getGreetingMsgs();
  std::vector<Item> &getInventory();
  
  // Setters
  void setDescription(QString newDescription);
  void setFrequency(int newFrequency);
  void setHatesPlayer(bool newHatesPlayer);
  void setReputation(int newReputation);
  void incrementTimesEncountered();
  void setDaysSinceEncountered(int newDaysSince);
  void setEncounterState(int newState);

private:
  QString name;
  QString description;
  QString briefKnown;
  QString briefUnknown;
  QString imagePath;
  QString location;
  int frequency;
  bool hatesPlayer;
  int reputation;
  int daysSinceEncountered;
  int timesEncountered;
  int encounterState;
  QMap<int, QString> greetingMsgs;
  std::vector<Item> inventory;
};

extern Character amos;
extern Character ira;

// Manages our Character objects
class Ensemble {
public:
  Ensemble();
  static constexpr int AMOS_INDEX = 0;
  static constexpr int IRA_INDEX = 1;
  Character *getCharacter(int index);
  std::vector<Character> &getCharacters();
  bool isCharacterName(QString target);

private:
  std::vector<Character> characters;
};

extern Ensemble ensembleObj;

#endif

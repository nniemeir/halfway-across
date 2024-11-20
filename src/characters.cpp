#include "../include/characters.h"

QString Character::getName() const { return name; }
QString Character::getDescription() const { return description; }
QString Character::getBrief() const { return brief; }
QString Character::getLocation() const { return location; }

int Character::getDaysSinceEncountered() const { return daysSinceEncountered; }

int Character::getTimesEncountered() const { return timesEncountered; }

int Character::getEncounterState() const { return encounterState; }

int Character::getFrequency() const { return frequency; }

bool Character::getHatesPlayer() const { return hatesPlayer; }

int Character::getReputation() const { return reputation; }

std::vector<Item> &Character::getInventory() { return inventory; }
void Character::setDescription(QString newDescription) {
  description = newDescription;
}

void Character::setDaysSinceEncountered(int newDaysSince) {
  daysSinceEncountered = newDaysSince;
}

void Character::setTimesEncountered(int newTimesEncountered) {
  timesEncountered = newTimesEncountered;
}

void Character::setEncounterState(int newState) { encounterState = newState; }

void Character::setFrequency(int newFrequency) { frequency = newFrequency; }

void Character::setHatesPlayer(bool newHatesPlayer) {
  hatesPlayer = newHatesPlayer;
}

void Character::setReputation(int newReputation) { reputation = newReputation; }

std::vector<Item> amosInv = {
    {"FELT HAT", 1, 1, 5, 0, "CLOTHING", "NONE",
     "It was a small hat, providing almost no warmth."}};

Character amos("Amos",
               "He was an older man with a large gray beard, dressed "
               "entirely in furs. I imagined he had been here for many years.",
               "I spotted a trapper as I approached.",
               ":/images/characters/amos.png", "The forest path", 14, false, 50,
               0, 0, 0, amosInv);

std::vector<Item> iraInv = {
    {"FELT HAT", 1, 1, 5, 0, "CLOTHING", "NONE",
     "It was a small hat, providing almost no warmth."}};

Character
    ira("Ira",
        "He was a disheveled looking man with scraggly ginger facial hair.",
        "There was a bewildered looking traveler at the fork in the road.",
        ":/images/characters/ira.png", "The forest path", 7, false, 50, 0, 0, 0,
        iraInv);

Ensemble ensembleObj;

Ensemble::Ensemble() { characters = {amos, ira}; }

std::vector<Character> &Ensemble::getCharacters() { return characters; }

Character *Ensemble::getCharacter(int index) { return &characters[index]; }

QString Character::getImage() const { return image; }

bool Ensemble::isCharacterName(QString target) {
  for (const auto &characterObj : characters) {
    if (QString::compare(target, characterObj.getName(), Qt::CaseInsensitive) ==
        0) {
      return true;
    }
  }
  return false;
}

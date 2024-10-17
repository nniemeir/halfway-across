#include "../include/characters.h"

QString Character::getName() const { return name; }
QString Character::getDescription() const { return description; }

bool Character::getDaysSinceEncountered() const { return daysSinceEncountered; }

bool Character::getFrequency() const { return frequency; }

bool Character::getHatesPlayer() const { return hatesPlayer; }

std::vector<Item> &Character::getInventory() { return inventory; }
void Character::setDescription(QString newDescription) {
  description = newDescription;
}

void Character::setDaysSinceEncountered(int newDaysSince) {
  daysSinceEncountered = newDaysSince;
}

void Character::setFrequency(int newFrequency) { frequency = newFrequency; }

void Character::setHatesPlayer(bool newHatesPlayer) {
  hatesPlayer = newHatesPlayer;
}

std::vector<Item> amosInv = {
    {"FELT HAT", 1, 1, 5, 0, "CLOTHING", "NONE",
     "It was a small hat, providing almost no warmth."}};

Character amos("Amos",
               "Amos was an older man with a large black beard, dressed "
               "entirely in furs. I imagined he had been here for many years.",
               7, false, 0, 0, amosInv);

std::vector<Item> iraInv = {
    {"FELT HAT", 1, 1, 5, 0, "CLOTHING", "NONE",
     "It was a small hat, providing almost no warmth."}};

Character
    ira("Ira",
        "Ira was a disheveled looking man with scraggly ginger facial hair.",
        14, false, 0, 0, iraInv);

Ensemble ensembleObj;

Ensemble::Ensemble() { characters = {amos, ira}; }

std::vector<Character> &Ensemble::getCharacters() { return characters; }

Character *Ensemble::getCharacter(int index) { return &characters[index]; }

bool Ensemble::isCharacterName(QString target) {
  for (const auto &characterObj : characters) {
    if (QString::compare(target, characterObj.getName(), Qt::CaseInsensitive) ==
        0) {
      return true;
    }
  }
  return false;
}

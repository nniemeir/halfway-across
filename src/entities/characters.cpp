#include "../../include/entities/characters.h"

QString Character::getName() const { return name; }

QString Character::getDescription() const { return description; }

QString Character::getBriefKnown() const { return briefKnown; }

QString Character::getBriefUnknown() const { return briefUnknown; }

QString Character::getImagePath() const { return imagePath; }

QString Character::getLocation() const { return location; }

int Character::getFrequency() const { return frequency; }

bool Character::getHatesPlayer() const { return hatesPlayer; }

int Character::getReputation() const { return reputation; }

int Character::getTimesEncountered() const { return timesEncountered; }

int Character::getDaysSinceEncountered() const { return daysSinceEncountered; }

int Character::getEncounterState() const { return encounterState; }

QMap<int, QString> &Character::getGreetingMsgs() { return greetingMsgs; }

std::vector<Item> &Character::getInventory() { return inventory; }

void Character::setDescription(QString newDescription) {
  description = newDescription;
}

void Character::setFrequency(int newFrequency) { frequency = newFrequency; }

void Character::setHatesPlayer(bool newHatesPlayer) {
  hatesPlayer = newHatesPlayer;
}

void Character::setReputation(int newReputation) { reputation = newReputation; }

void Character::incrementTimesEncountered() { timesEncountered++; }

void Character::setDaysSinceEncountered(int newDaysSince) {
  daysSinceEncountered = newDaysSince;
}

void Character::setEncounterState(int newState) { encounterState = newState; }

std::vector<Item> amosInv = {{"FELT HAT",
                              "It was a small hat, providing almost no warmth.",
                              "CLOTHING", "NONE", 1, false, 5, 0}};

Character amos(
    "Amos",
    "He was an older man with a large gray beard, dressed "
    "entirely in furs. I imagined he had been here for many years.",
    "I spotted a trapper as I approached.",
    "I saw Amos leaning on a tree as I neared the fork in the path.",
    ":/images/characters/amos.png", "The forest path", 14, false, 50, 0, 0, 0,
    amosInv,
    {{0, "Hey there, been a moment since I've seen a new face in these parts. "
         "My name's Amos, where do you come from? (I could: tell Amos about "
         "Arkansas, tell Amos about Iowa, tell Amos about Kansas)\n\nHint: I "
         "can use the command GOODBYE to end a conversation."},
     {1, ""}});

std::vector<Item> iraInv = {{"FELT HAT",
                             "It was a small hat, providing almost no warmth.",
                             "CLOTHING", "NONE", 1, false, 5, 0}};

Character ira(
    "Ira", "He was a disheveled looking man with scraggly ginger facial hair.",
    "There was a bewildered looking traveler at the fork in the path.",
    "I noticed Ira was at the fork in the path.", ":/images/characters/ira.png",
    "The forest path", 7, false, 50, 0, 0, 0, iraInv, {{0, "PLACEHOLDER MSG"}});

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

Ensemble ensembleObj;

#include "../../include/characters.h"
#include "../../include/scenarios.h"
#include "../../include/world.h"

const int TOLD_ORIGIN = 1;
const int ASK_HIMSELF = 2;
const int ASK_HUNTING = 3;
const int ASK_FISHING = 4;

QString Scenario::askAmosE1(QString subject, Location *location) {
  if (worldObj.getActiveCharacter()->getEncounterState() == TOLD_ORIGIN) {
    return askAmosE1S1(subject, location);
  } else {
    return "I asked you first.";
  }
}

QString Scenario::askAmosE1S1(QString subject, Location *location) {
  if (subject == "HIMSELF") {
    worldObj.getActiveCharacter()->setEncounterState(ASK_HIMSELF);
    return "There's not much to tell. I was drafted into the war as soon as I "
           "was old enough and fought under that coward Bragg in the Battle of "
           "Perryville. By the time the war ended, I had lost most of my "
           "decent relatives so it just didn't feel like home anymore and it "
           "wasn't long before I headed this way to try my hand at trapping. "
           "(I could: tell Amos about my support for the Confederacy, tell "
           "Amos about my support for the Union.";
  } else if (subject == "HUNTING") {
    worldObj.getActiveCharacter()->setEncounterState(ASK_HUNTING);
    return "PLACEHOLDER MSG";
  } else if (subject == "FISHING") {
    worldObj.getActiveCharacter()->setEncounterState(ASK_FISHING);
    return "PLACEHOLDER MSG";
  }
  return "";
}

QString Scenario::tellAmosE1(QString subject, Location *location) {
  if (worldObj.getActiveCharacter()->getEncounterState() == START) {
    return tellAmosE1S0(subject, location);
  } else if (worldObj.getActiveCharacter()->getEncounterState() ==
             ASK_HIMSELF) {
    return tellAmosE1S3(subject, location);
  } else if (worldObj.getActiveCharacter()->getEncounterState() == END) {
    return "I don't have anymore time to talk.";
  } else {
    return "";
  }
}

QString Scenario::tellAmosE1S0(QString subject, Location *location) {
  QString nextPromptMsg = "(Ask Amos about himself, ask Amos about hunting, "
                          "ask Amos about fishing)";
  if (subject == "ARKANSAS") {
    worldObj.getActiveCharacter()->setReputation(
        worldObj.getActiveCharacter()->getReputation() + 15);
    worldObj.getActiveCharacter()->setEncounterState(TOLD_ORIGIN);
    return "Arkansas, huh? I've known some good men from there. " +
           nextPromptMsg;
  } else if (subject == "IOWA") {
    worldObj.getActiveCharacter()->setReputation(
        worldObj.getActiveCharacter()->getReputation() - 20);
    worldObj.getActiveCharacter()->setEncounterState(TOLD_ORIGIN);
    return "Iowa, huh? I'll try not to hold that against ya. " + nextPromptMsg;
  } else if (subject == "KANSAS") {
    worldObj.getActiveCharacter()->setEncounterState(TOLD_ORIGIN);
    return "Kansas, huh? I'll have to keep an eye on you. " + nextPromptMsg;
  } else {
    return "";
  }
}

QString Scenario::tellAmosE1S3(QString subject, Location *location) {
  if (subject == "MY SUPPORT FOR CONFEDERACY") {
    worldObj.getActiveCharacter()->setReputation(
        worldObj.getActiveCharacter()->getReputation() + 15);
    worldObj.getActiveCharacter()->setEncounterState(END);
    return "Maybe we have more in common than I thought. I imagine I'll see "
           "you the next time I come through here, farewell.";
  } else if (subject == "MY SUPPORT FOR UNION") {
    worldObj.getActiveCharacter()->setHatesPlayer(true);
    worldObj.getActiveCharacter()->setEncounterState(END);
    return "Then you'll get no help from me, goodbye.";
  }
  return "";
}

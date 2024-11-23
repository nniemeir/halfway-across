#include "../../../include/core/world.h"
#include "../../../include/entities/characters.h"
#include "../../../include/entities/dialogue.h"

static constexpr int TOLD_ORIGIN = 1;
static constexpr int ASK_HIMSELF = 2;

QString Dialogue::askAmosE1(QString subject, Location *location) {
  if (worldObj.getActiveCharacter()->getEncounterState() == TOLD_ORIGIN) {
    return askAmosE1S1(subject, location);
  }
  return ASK_INVALID;
}

QString Dialogue::askAmosE1S1(QString subject, Location *location) {
  if (subject == "HIMSELF") {
    worldObj.getActiveCharacter()->setEncounterState(ASK_HIMSELF);
    promptMsg =
        "(I could: tell Amos about my support for the Confederacy, tell "
        "Amos about my support for the Union.)";
    return "There's not much to tell. I was drafted into the war as soon as I "
           "was old enough and fought under that coward Bragg in the Battle of "
           "Perryville. By the time the war ended, I had lost most of my "
           "decent relatives so it just didn't feel like home anymore and it "
           "wasn't long before I headed this way to try my hand at trapping. ";
  }
  if (subject == "HUNTING" || subject == "FISHING") {
    return ASK_REFUSAL;
  }
  return "";
}

QString Dialogue::tellAmosE1(QString subject, Location *location) {
  if (worldObj.getActiveCharacter()->getEncounterState() == START) {
    return tellAmosE1S0(subject, location);
  }
  if (worldObj.getActiveCharacter()->getEncounterState() == ASK_HIMSELF) {
    return tellAmosE1S3(subject, location);
  }
  if (worldObj.getActiveCharacter()->getEncounterState() == END) {
    return DIALOGUE_OVER;
  }
  return "";
}

QString Dialogue::tellAmosE1S0(QString subject, Location *location) {
  promptMsg = "(I could: ask Amos about himself, ask Amos about hunting, "
              "ask Amos about fishing)";
  if (subject == "ARKANSAS") {
    worldObj.getActiveCharacter()->setReputation(
        worldObj.getActiveCharacter()->getReputation() + 15);
    worldObj.getActiveCharacter()->setEncounterState(TOLD_ORIGIN);
    return "Arkansas, huh? I've known some good men from there.";
  }
  if (subject == "IOWA") {
    worldObj.getActiveCharacter()->setReputation(
        worldObj.getActiveCharacter()->getReputation() - 20);
    worldObj.getActiveCharacter()->setEncounterState(TOLD_ORIGIN);
    return "Iowa, huh? I'll try not to hold that against ya.";
  }
  if (subject == "KANSAS") {
    worldObj.getActiveCharacter()->setEncounterState(TOLD_ORIGIN);
    return "Kansas, huh? I'll have to keep an eye on you.";
  }
  return "";
}

QString Dialogue::tellAmosE1S3(QString subject, Location *location) {
  if (subject == "MY SUPPORT FOR CONFEDERACY") {
    worldObj.getActiveCharacter()->setReputation(
    worldObj.getActiveCharacter()->getReputation() + 15);
    worldObj.getActiveCharacter()->setEncounterState(END);
    promptMsg = "(I could: GOODBYE)";
    return "Maybe we have more in common than I thought. I imagine I'll see "
           "you the next time I come through here, farewell.";
  }
  if (subject == "MY SUPPORT FOR UNION") {
    worldObj.getActiveCharacter()->setHatesPlayer(true);
    worldObj.getActiveCharacter()->setEncounterState(END);
    promptMsg = "(I could: GOODBYE)";
    return "Then you'll get no help from me, goodbye.";
  }
  return "";
}

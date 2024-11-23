#include "../../../include/core/audio.h"
#include "../../../include/core/handling/encounterhandler.h"
#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/dialogue.h"

EncounterHandler::EncounterHandler() { initEncounters(); }

void EncounterHandler::initEncounters() {
    askAmosEncounters = {{0, [this](QString subject, Location *location) {
                              return dialogueObj.askAmosE1(subject, location);
                          }}};

    askIraEncounters = {{0, [this](QString subject, Location *location) {
                             return dialogueObj.askIraE1(subject, location);
                         }}};

    tellAmosEncounters = {{0, [this](QString subject, Location *location) {
                               return dialogueObj.tellAmosE1(subject, location);
                           }}};

    tellIraEncounters = {{0, [this](QString subject, Location *location) {
                              return dialogueObj.tellIraE1(subject, location);
                          }}};
}


void EncounterHandler::talkLogic(MainWindow *mainWindow, QString verb, QString target, QString subject, Location *location) {
    QString responseMsg = getResponseMsg(verb, target, subject, location);

    if (!responseMsg.isEmpty()) {
        talkPlayVoice(verb);
        mainWindow->setDescription(responseMsg);
        mainWindow->appendDescription(dialogueObj.getPromptMsg());
        return;
    }
    msgHandlerObj.invalidTopicMsg(mainWindow);
    mainWindow->appendDescription(dialogueObj.getPromptMsg());
}

QString EncounterHandler::getResponseMsg(QString verb, QString target, QString subject,
                                         Location *location) {
    int timesEncountered = worldObj.getActiveCharacter()->getTimesEncountered();
    if (verb == "ASK") {
        if (target == "AMOS") {
            return askAmosEncounters[timesEncountered](subject, location);
        }
        return askIraEncounters[timesEncountered](subject, location);
    }
    if (target == "AMOS") {
        return tellAmosEncounters[timesEncountered](subject, location);
    }
    return tellIraEncounters[timesEncountered](subject, location);
}

void EncounterHandler::talkPlayVoice(QString verb) {
    if (verb == "ASK") {
        sfxPlayer.play("qrc:/audio/sfx/ask.mp3", sfxPlayer.getdefSfxVol(), 0);
        return;
    }
    sfxPlayer.play("qrc:/audio/sfx/tell.mp3", sfxPlayer.getdefSfxVol(), 0);
}

EncounterHandler encounterHandlerObj;

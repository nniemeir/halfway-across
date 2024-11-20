#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/scenarios.h"
#include "../../include/world.h"

void Handling::tell(MainWindow *mainWindow, QString target, QString subject,
                    Location *location) {
  if (worldObj.getActiveCharacter() != nullptr) {
    QMap<QString, std::function<void()>> validCharacters{
        {"AMOS", [mainWindow, subject, location,
                  this]() { tellAmos(mainWindow, subject, location); }},
        {"IRA", [mainWindow, subject, location, this]() {
           tellIra(mainWindow, subject, location);
         }}};
    if (validCharacters.contains(target)) {
      if (QString::compare(target, worldObj.getActiveCharacter()->getName(),
                           Qt::CaseInsensitive) == 0) {
        sfxPlayer.play("qrc:/audio/sfx/tell.mp3", sfxPlayer.getdefSfxVol(), 0);
        validCharacters[target]();
        return;
      }
    }
  }
  characterNotActiveMsg(mainWindow, target);
}

void Handling::tellAmos(MainWindow *mainWindow, QString subject,
                        Location *location) {
  if (worldObj.getGreetedNPC()) {
    QString responseMsg;
    if (worldObj.getActiveCharacter()->getTimesEncountered() == 0) {
      responseMsg = scenarioObj.tellAmosE1(subject, location);
    }
    if (responseMsg != "") {
      mainWindow->setDescription(responseMsg);
    } else {
      invalidTopicMsg(mainWindow);
    }
  } else {
    notGreetedMsg(mainWindow);
  }
}

void Handling::tellIra(MainWindow *mainWindow, QString subject,
                       Location *location) {
  if (worldObj.getGreetedNPC()) {
    QString responseMsg;
    if (worldObj.getActiveCharacter()->getTimesEncountered() == 0) {
      responseMsg = scenarioObj.tellIraE1(subject, location);
    }
    if (responseMsg != "") {
      mainWindow->setDescription(responseMsg);
    } else {
      invalidTopicMsg(mainWindow);
    }
  } else {
    notGreetedMsg(mainWindow);
  }
}

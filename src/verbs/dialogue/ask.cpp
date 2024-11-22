#include "../../../include/core/audio.h"
#include "../../../include/core/handling.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/dialogue.h"

void Handling::ask(MainWindow *mainWindow, QString target, QString subject,
                   Location *location) {
  if (worldObj.getActiveCharacter() != nullptr) {
    QMap<QString, std::function<void()>> validCharacters{
        {"AMOS", [mainWindow, subject, location,
                  this]() { askAmos(mainWindow, subject, location); }},
        {"IRA", [mainWindow, subject, location, this]() {
           askIra(mainWindow, subject, location);
         }}};
    if (validCharacters.contains(target)) {
      if (QString::compare(target, worldObj.getActiveCharacter()->getName(),
                           Qt::CaseInsensitive) == 0) {
        sfxPlayer.play("qrc:/audio/sfx/ask.mp3", sfxPlayer.getdefSfxVol(),
                       false);
        validCharacters[target]();
        return;
      }
    }
  }
  characterNotActiveMsg(mainWindow, target);
}

void Handling::askAmos(MainWindow *mainWindow, QString subject,
                       Location *location) {
  QString responseMsg;
  if (worldObj.getActiveCharacter()->getTimesEncountered() == 0) {
    responseMsg = scenarioObj.askAmosE1(subject, location);
  }
  if (responseMsg != "") {
    mainWindow->setDescription(responseMsg);
  } else {
    invalidTopicMsg(mainWindow);
  }
}

void Handling::askIra(MainWindow *mainWindow, QString subject,
                      Location *location) {
  QString responseMsg;
  if (worldObj.getActiveCharacter()->getTimesEncountered() == 0) {
    responseMsg = scenarioObj.askIraE1(subject, location);
  }
  if (responseMsg != "") {
    mainWindow->setDescription(responseMsg);
  } else {
    invalidTopicMsg(mainWindow);
  }
}

#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/world.h"

void Handling::ask(MainWindow *mainWindow, QString target, QString subject,
                   Location *location) {
  if (worldObj.getActiveCharacter() != nullptr) {
    QMap<QString, std::function<void()>> validCharacters;
    validCharacters["AMOS"] = [mainWindow, subject, location, this]() {
      askAmos(mainWindow, subject, location);
    };
    validCharacters["IRA"] = [mainWindow, subject, location, this]() {
      askIra(mainWindow, subject, location);
    };
    if (validCharacters.contains(target)) {
      if (QString::compare(target, worldObj.getActiveCharacter()->getName(),
                           Qt::CaseInsensitive) == 0) {
        sfxPlayer.play("qrc:/audio/sfx/ask.mp3", sfxPlayer.getdefSfxVol(), 0);
        validCharacters[target]();
        return;
      }
    }
  }
  characterNotActiveMsg(mainWindow, target);
}

void Handling::askAmos(MainWindow *mainWindow, QString subject,
                       Location *location) {
  mainWindow->setDescription(
      "Placeholder message for telling Amos about subjects.");
}

void Handling::askIra(MainWindow *mainWindow, QString subject,
                      Location *location) {
  mainWindow->setDescription(
      "Placeholder message for telling Ira about subjects.");
}

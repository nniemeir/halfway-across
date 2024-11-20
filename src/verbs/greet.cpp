#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/scenarios.h"
#include "../../include/world.h"

void Handling::greet(MainWindow *mainWindow) {
  if (!worldObj.getSocialized()) {
    if (worldObj.getActiveCharacter() != nullptr) {
      if (worldObj.getActiveCharacter()->getHatesPlayer()) {
        mainWindow->setDescription(
            QString("%1 was unwilling to speak to me.")
                .arg(worldObj.getActiveCharacter()->getName()));
        return;
      }
      mainWindow->setCompassImage("");
      QMap<QString, std::function<QString()>> validCharacters = {
          {"Amos", [this]() { return scenarioObj.greetAmos(); }},
          {"Ira", [this]() { return scenarioObj.greetIra(); }}};
      sfxPlayer.play("qrc:/audio/sfx/ask.mp3", sfxPlayer.getdefSfxVol(), 0);
      QString characterName = worldObj.getActiveCharacter()->getName();
      QString greetingMessage = validCharacters[characterName]();
      mainWindow->setDescription(greetingMessage);
      mainWindow->setSettingImage(worldObj.getActiveCharacter()->getImage());
      worldObj.setGreetedNPC(1);
    } else {
      mainWindow->setDescription("There was no one around to greet.");
    }
  } else {
    mainWindow->setDescription(
        QString("I had already spoken to %1 that day.")
            .arg(worldObj.getActiveCharacter()->getName()));
  }
}

#include "../../../include/core/audio.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/dialogue.h"

void VerbHandler::greet(MainWindow *mainWindow) {
auto activeCharacter = worldObj.getActiveCharacter();
if (activeCharacter == nullptr) {
    mainWindow->setDescription("There was no one around to greet.");
    return;
}
  if (worldObj.getSocialized()) {
    mainWindow->setDescription(
        QString("I had already spoken to %1 that day.")
            .arg(activeCharacter->getName()));
    return;
  }

  if (activeCharacter->getHatesPlayer()) {
    mainWindow->setDescription(
        QString("%1 was unwilling to speak to me.")
            .arg(activeCharacter->getName()));
    return;
  }
  mainWindow->setCompassImage("");
  QMap<QString, std::function<QString()>> validCharacters = {
      {"Amos", [this]() { return dialogueObj.greetAmos(); }},
      {"Ira", [this]() { return dialogueObj.greetIra(); }}};
  sfxPlayer.play("qrc:/audio/sfx/ask.mp3", sfxPlayer.getdefSfxVol(), false);
  QString characterName = activeCharacter->getName();
  QString greetingMessage = validCharacters[characterName]();
  mainWindow->setDescription(greetingMessage);
  mainWindow->setLocationImage(activeCharacter->getImage());
  worldObj.setGreetedNPC(true);
}

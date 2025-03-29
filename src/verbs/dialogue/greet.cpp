#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"
#include "../../../include/entities/dialogue.h"

void VerbHandler::greet(MainWindow *mainWindow) {
  auto activeCharacter = worldObj.getActiveCharacter();
  if (activeCharacter == nullptr) {
    mainWindow->setDescription("There was no one around to greet.");
    return;
  }
  if (worldObj.getConversedToday()) {
    mainWindow->setDescription(QString("I had already spoken to %1 that day.")
                                   .arg(activeCharacter->getName()));
    return;
  }

  if (activeCharacter->getHatesPlayer()) {
    mainWindow->setDescription(QString("%1 was unwilling to speak to me.")
                                   .arg(activeCharacter->getName()));
    return;
  }
  mainWindow->setCompassImage("");
  QMap<QString, int> characterIndices = {{"Amos", Ensemble::AMOS_INDEX},
                                         {"Ira", Ensemble::IRA_INDEX}};
  mainWindow->playSfx("qrc:/audio/sfx/ask.mp3");
  QString characterName = activeCharacter->getName();
  QString greetingMsg = dialogueObj.greetLogic(characterIndices[characterName]);
  mainWindow->setDescription(greetingMsg);
  mainWindow->setLocationImage(activeCharacter->getImagePath());
  worldObj.setConversing(true);
}

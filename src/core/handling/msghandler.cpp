#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/audio.h"
#include "../../../include/core/world.h"
#include <QDebug>

MsgHandler::MsgHandler() {}

void MsgHandler::gameOverMsg(MainWindow *mainWindow, QString reason) {
  QMap<QString, QString> stat = {
      {"HEALTH", "My injuries were too grave for me to continue."},
      {"HUNGER", "I succumbed to my hunger."},
      {"MENTAL", "I had lost the will to continue."},
      {"THIRST", "I succumbed to my thirst."},
      {"WARMTH", "I could no longer bear the cold."}};

  if (stat.contains(reason)) {
    mainWindow->setDescription(perished.setDescription(stat.value(reason)));
  } else {
    qDebug() << "Unable to determine reason for game over.";
  }
  mainWindow->setLocation(worldObj.getCurrentLocation()->getMusicPath(),
                          worldObj.getCurrentLocation()->getAmbiencePath(),
                          &perished);
  sfxPlayer.play("qrc:/audio/sfx/perished.mp3", sfxPlayer.getdefSfxVol(),
                 false);
}

void MsgHandler::characterNotActiveMsg(MainWindow *mainWindow, QString target) {
  mainWindow->setDescription(
      QString("I didn't see anyone by the description of %1 in the area.")
          .arg(target.toLower()));
}

void MsgHandler::confusedMsg(MainWindow *mainWindow) {
  mainWindow->setDescription(
      "My thoughts were pushing me in a nonsensical direction.");
}

void MsgHandler::invalidTopicMsg(MainWindow *mainWindow) {
  mainWindow->setDescription("It didn't seem like an appropriate topic.");
}

void MsgHandler::missingItemMsg(MainWindow *mainWindow, QString target) {
  mainWindow->setDescription(
      QString("I didn't have %1.").arg(target.toLower()));
}

void MsgHandler::notAllowedDirMsg(MainWindow *mainWindow, QString verb,
                                  QString target) {
  mainWindow->setDescription(
      QString("I couldn't %1 %2 there.").arg(verb.toLower(), target.toLower()));
}

void MsgHandler::notAllowedInLocMsg(MainWindow *mainWindow, QString action) {
  mainWindow->setDescription(
      QString("I couldn't %1 there.").arg(action.toLower()));
}

void MsgHandler::notGreetedMsg(MainWindow *mainWindow) {
  mainWindow->setDescription(
      "I should greet someone before trying to have a conversation.");
}

void MsgHandler::tiredMsg(MainWindow *mainWindow) {
  mainWindow->setDescription(
      "I didn't have the energy to travel anywhere else that day.\n");
}

void MsgHandler::waitMsg(MainWindow *mainWindow) {
  mainWindow->setDescription("I waited a while.");
}

MsgHandler msgHandlerObj;

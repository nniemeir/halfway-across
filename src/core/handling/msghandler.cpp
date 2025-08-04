#include "core/handling/msghandler.h"

MsgHandler::MsgHandler() {}

const QString MsgHandler::CHARACTER_NOT_ACTIVE =
    "I didn't see anyone by that description nearby.";
const QString MsgHandler::CONFUSED =
    "My thoughts were pushing me in a nonsensical direction.";
const QString MsgHandler::DIALOGUE_OVER = "I don't have anymore time to talk.";
const QString MsgHandler::TOPIC_INVALID =
    "It didn't seem like an appropriate topic.";
const QString MsgHandler::TOPIC_REFUSAL =
    "I'm not sure I know you well enough to get into that.";
const QString MsgHandler::NOT_GREETED =
    "I should greet someone before trying to have a conversation.";
const QString MsgHandler::TIRED =
    "I didn't have the energy to travel anywhere else that day.";
const QString MsgHandler::WAIT = "I waited a while.";

QString MsgHandler::gameOver(QString reason) {
  static const QMap<QString, QString> stat = {
      {"HEALTH", "My injuries were too grave for me to continue."},
      {"HUNGER", "I succumbed to my hunger."},
      {"MENTAL", "I had lost the will to continue."},
      {"THIRST", "I succumbed to my thirst."},
      {"WARMTH", "I could no longer bear the cold."}};

  if (stat.contains(reason)) {
    return perished.setDescription(stat.value(reason));
  }
  return "Unable to determine reason for game over.";
}

QString MsgHandler::invalidDirection(QString verb, QString target) {
  return "I couldn't " + verb.toLower() + target.toLower() + " there.";
}

QString MsgHandler::invalidLocation(QString verb) {
  return "I couldn't " + verb.toLower() + " there.";
}

QString MsgHandler::missingItem(QString target) {
  return "I didn't have " + target.toLower() + " in my possession.";
}

MsgHandler msgHandlerObj;

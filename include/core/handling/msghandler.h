#ifndef MSGHANDLER_H
#define MSGHANDLER_H
#include "../../../include/ui/mainwindow.h"

class MsgHandler {
public:
  MsgHandler();
  static const QString CHARACTER_NOT_ACTIVE;
  static const QString CONFUSED;
  static const QString DIALOGUE_OVER;
  static const QString TOPIC_INVALID;
  static const QString TOPIC_REFUSAL;
  static const QString NOT_GREETED;
  static const QString TIRED;
  static const QString WAIT;
  QString gameOver(QString reason);
  QString invalidDirection(QString verb, QString target);
  QString invalidLocation(QString verb);
  QString missingItem(QString target);
};

extern MsgHandler msgHandlerObj;

#endif

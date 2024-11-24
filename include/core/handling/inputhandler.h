#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "../../../include/ui/mainwindow.h"

class InputHandler {
public:
  InputHandler();
  static constexpr int VERB_ARG = 0;
  static constexpr int VERB_INVALID = -1;
  static constexpr int VERB_NO_ARG = 1;

  // Formatting
  QString getArticle(QString target);
  // Script
  QString getLastCommand() const;
  void setLastCommand(QString command);
  // General handling
  void parse(MainWindow *mainWindow, QString input);
  int getVerbType(QString input);

private:
  static void initFillerWords(const QStringList &words);
  QString removeFillerWords(const QString &text);
  QStringList fillerWords;
  static QRegularExpression fillerWordsRegex;
  static const QRegularExpression multiSpaces;
  QString lastCommand;
};
extern InputHandler inputHandlerObj;

#endif // INPUTHANDLER_H

#include "core/handling/inputhandler.h"
#include "core/handling/verbhandler.h"
#include "core/world.h"
#include <QDebug>

InputHandler::InputHandler() {
  fillerWords = {"A", "AN", "AT", "COOKED", "FROM", "IN", "THE", "TO"};
  initFillerWords(fillerWords);
}

QString InputHandler::getArticle(QString target) {
  static const QStringList vowels = {"A", "E", "I", "O", "U"};
  QString firstLetter = target.at(0).toUpper();
  if (vowels.contains(firstLetter)) {
    return "an";
  }
  return "a";
}

QString InputHandler::getLastCommand() const { return lastCommand; }

void InputHandler::setLastCommand(QString command) { lastCommand = command; }

void InputHandler::parse(MainWindow *mainWindow, QString input) {
  input = removeFillerWords(input);
  QStringList parts = input.split(" ", Qt::SkipEmptyParts);

  QString verb;
  QString target;
  QString subject;

  if (!parts.isEmpty()) {
    verb = parts.at(0);
    for (int i = 1; i < parts.size(); ++i) {
      if (parts.at(i) == "ABOUT" || parts.at(i) == "ON") {
        target = parts.mid(1, i - 1).join(" ").trimmed();
        subject = parts.mid(i + 1).join(" ").trimmed();
        break;
      }
    }

    if (target.isEmpty() && parts.size() > 1) {
      target = parts.mid(1).join(" ").trimmed();
      subject = "";
    }
  }

  if (target.isEmpty()) {
    mainWindow->setDescription(
        QString("I didn't know what to %1.").arg(verb.toLower()));
    return;
  }
  verbHandlerObj.process(mainWindow, verb, target, subject,
                         worldObj.getCurrentLocation());
}

// Inputted verb must match an element of argVerbs or noArgVerbs to be
// considered valid
int InputHandler::getVerbType(QString input) {
  QString inputVerb = input.split(" ").at(0);
  static const QMap<QString, int> validVerbs{
      {"ASK", VERB_ARG},         {"BEGIN", VERB_NO_ARG},
      {"COOK", VERB_ARG},        {"CRAFT", VERB_ARG},
      {"CRY", VERB_NO_ARG},      {"DIAGNOSE", VERB_NO_ARG},
      {"DRINK", VERB_ARG},       {"DROP", VERB_ARG},
      {"E", VERB_NO_ARG},        {"EAST", VERB_NO_ARG},
      {"EAT", VERB_ARG},         {"EXAMINE", VERB_ARG},
      {"EXIT", VERB_NO_ARG},     {"FILL", VERB_ARG},
      {"GO", VERB_ARG},          {"GOODBYE", VERB_NO_ARG},
      {"GREET", VERB_NO_ARG},    {"HELP", VERB_NO_ARG},
      {"HUNT", VERB_ARG},        {"L", VERB_ARG},
      {"LOAD", VERB_ARG},        {"LOOK", VERB_ARG},
      {"MOVE", VERB_ARG},        {"N", VERB_NO_ARG},
      {"NORTH", VERB_NO_ARG},    {"PUT", VERB_ARG},
      {"Q", VERB_NO_ARG},        {"QUIT", VERB_NO_ARG},
      {"R", VERB_NO_ARG},        {"READ", VERB_ARG},
      {"REFLECT", VERB_NO_ARG},  {"REMOVE", VERB_ARG},
      {"S", VERB_NO_ARG},        {"SCREAM", VERB_NO_ARG},
      {"SCRIPT", VERB_NO_ARG},   {"SHOOT", VERB_ARG},
      {"SHOUT", VERB_NO_ARG},    {"SIT", VERB_ARG},
      {"SKIN", VERB_ARG},        {"SLEEP", VERB_NO_ARG},
      {"SOUTH", VERB_NO_ARG},    {"STAND", VERB_ARG},
      {"TAKE", VERB_ARG},        {"TELL", VERB_ARG},
      {"UNSCRIPT", VERB_NO_ARG}, {"USE", VERB_ARG},
      {"VERSION", VERB_NO_ARG},  {"W", VERB_NO_ARG},
      {"WAIT", VERB_NO_ARG},     {"WEAR", VERB_ARG},
      {"WEST", VERB_NO_ARG},     {"X", VERB_NO_ARG},
      {"YELL", VERB_NO_ARG},     {"Z", VERB_NO_ARG}};
  if (validVerbs.contains(inputVerb)) {
    return validVerbs.value(inputVerb);
  }
  return VERB_INVALID;
}

void InputHandler::initFillerWords(const QStringList &words) {
  QString pattern = QString("\\b(%1)\\b").arg(words.join("|"));
  fillerWordsRegex = QRegularExpression(pattern);
}

QString InputHandler::removeFillerWords(const QString &text) {
  QString modifiedText = text;
  modifiedText.remove(fillerWordsRegex);
  return modifiedText.trimmed().replace(multiSpaces, " ");
}

QRegularExpression InputHandler::fillerWordsRegex;

const QRegularExpression InputHandler::multiSpaces(R"(\s+)");

InputHandler inputHandlerObj;

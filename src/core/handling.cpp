#include "../../include/core/audio.h"
#include "../../include/core/handling.h"
#include "../../include/core/world.h"
#include <QDebug>

Handling::Handling() {
  fillerWords = {"A", "AN", "AT", "COOKED", "FROM", "IN", "THE", "TO"};
  initFillerWords(fillerWords);
}

QString Handling::getArticle(QString target) {
  QStringList vowels = {"A", "E", "I", "O", "U"};
  QString firstLetter = target.at(0).toUpper();
  if (vowels.contains(firstLetter)) {
    return "an";
  } else {
    return "a";
  }
}

QString Handling::getLastCommand() const { return lastCommand; }
void Handling::setLastCommand(QString command) { lastCommand = command; }

void Handling::handleVerb(MainWindow *mainWindow, QString verb, QString target,
                          QString subject, Location *location) {
  // The handling for the verb "AGAIN" is located in
  // MainWindow::handleReturnPressed
  if (verb == "EXIT" || verb == "Q" || verb == "QUIT") {
    mainWindow->closeProgram();
  } else {
    QMap<QString, std::function<void()>> dialogueActions{
        {"ASK", [mainWindow, target, subject, location,
                 this]() { ask(mainWindow, target, subject, location); }},
        {"GOODBYE",
         [mainWindow, location, this]() { goodbye(mainWindow, location); }},
        {"TELL", [mainWindow, target, subject, location, this]() {
           tell(mainWindow, target, subject, location);
         }}};
    QMap<QString, std::function<void()>> gameplayActions{
        {"COOK", [mainWindow, target, location,
                  this]() { cook(mainWindow, target, location); }},
        {"CRAFT", [mainWindow, target, this]() { craft(mainWindow, target); }},
        {"CRY", [mainWindow, this]() { cry(mainWindow); }},
        {"DIAGNOSE",
         [mainWindow, location, this]() { diagnose(mainWindow, location); }},
        {"DRINK", [mainWindow, target, location,
                   this]() { drink(mainWindow, target, location); }},
        {"DROP", [mainWindow, target, subject, location,
                  this]() { put(mainWindow, target, "GROUND", location); }},
        {"E", [mainWindow, verb, location,
               this]() { move(mainWindow, verb, location); }},
        {"EAT", [mainWindow, target, this]() { eat(mainWindow, target); }},
        {"EXAMINE", [mainWindow, target, location,
                     this]() { examine(mainWindow, target); }},
        {"FILL", [mainWindow, target, location,
                  this]() { fill(mainWindow, target, location); }},
        {"GO", [mainWindow, target, location,
                this]() { move(mainWindow, target, location); }},
        {"GREET",
         [mainWindow, target, location, this]() { greet(mainWindow); }},
        {"HELP", [mainWindow, target, this]() { help(mainWindow); }},
        {"HUNT", [mainWindow, target, location,
                  this]() { hunt(mainWindow, target, location); }},
        {"L", [mainWindow, target, location,
               this]() { look(mainWindow, target, location); }},
        {"LOAD", [mainWindow, target, this]() { load(mainWindow, target); }},
        {"LOOK", [mainWindow, target, location,
                  this]() { look(mainWindow, target, location); }},
        {"MOVE", [mainWindow, target, location,
                  this]() { move(mainWindow, target, location); }},
        {"N", [mainWindow, verb, location,
               this]() { move(mainWindow, verb, location); }},
        {"PUT", [mainWindow, target, subject, location,
                 this]() { put(mainWindow, target, subject, location); }},
        {"READ", [mainWindow, location, target,
                  this]() { read(mainWindow, location, target); }},
        {"R",
         [mainWindow, location, this]() { diagnose(mainWindow, location); }},
        {"REFLECT",
         [mainWindow, location, this]() { diagnose(mainWindow, location); }},
        {"REMOVE",
         [mainWindow, target, this]() { remove(mainWindow, target); }},
        {"S", [mainWindow, verb, location,
               this]() { move(mainWindow, verb, location); }},
        {"SCREAM",
         [mainWindow, location, this]() { yell(mainWindow, location); }},
        {"SCRIPT", [mainWindow, this]() { script(mainWindow); }},
        {"SHOOT", [mainWindow, target, location,
                   this]() { shoot(mainWindow, target, location); }},
        {"SHOUT",
         [mainWindow, location, this]() { yell(mainWindow, location); }},
        {"SIT", [mainWindow, target, location,
                 this]() { sit(mainWindow, target, location); }},
        {"SKIN", [mainWindow, target, location,
                  this]() { skin(mainWindow, target, location); }},
        {"SLEEP",
         [mainWindow, location, this]() { sleep(mainWindow, location); }},
        {"STAND", [mainWindow, this]() { stand(mainWindow); }},
        {"TAKE", [mainWindow, target, location,
                  this]() { take(mainWindow, target, location); }},
        {"UNSCRIPT", [mainWindow, this]() { unscript(mainWindow); }},
        {"USE", [mainWindow, target, location,
                 this]() { use(mainWindow, target, location); }},
        {"VERSION", [mainWindow, this]() { version(mainWindow); }},
        {"W", [mainWindow, verb, location,
               this]() { move(mainWindow, verb, location); }},
        {"WAIT",
         [mainWindow, location, this]() { wait(mainWindow, location); }},
        {"WEAR", [mainWindow, target, this]() { wear(mainWindow, target); }},
        {"X", [mainWindow, target, location,
               this]() { examine(mainWindow, target); }},
        {"YELL",
         [mainWindow, location, this]() { yell(mainWindow, location); }},
        {"Z", [mainWindow, location, this]() { wait(mainWindow, location); }}};
    QMap<QString, std::function<void()>> menuActions{
        {"BEGIN",
         [mainWindow, location, this]() { begin(mainWindow, location); }},
        {"HELP", [mainWindow, this]() { help(mainWindow); }}};

    if (worldObj.getGreetedNPC() && !worldObj.getSocialized()) {
      handleVerbActions(mainWindow, verb, target, subject, location,
                        dialogueActions, menuActions, gameplayActions);
      return;
    }
    if (location->getName() == "Perished Menu" ||
        location->getName() == "Introduction Menu") {
      handleVerbActions(mainWindow, verb, target, subject, location,
                        menuActions, dialogueActions, gameplayActions);
    } else {
      handleVerbActions(mainWindow, verb, target, subject, location,
                        gameplayActions, dialogueActions, menuActions);
    }
  }
}

void Handling::handleVerbActions(
    MainWindow *mainWindow, QString verb, QString target, QString subject,
    Location *location, QMap<QString, std::function<void()>> validActions,
    QMap<QString, std::function<void()>> invalidActions1,
    QMap<QString, std::function<void()>> invalidActions2) {
  if (validActions.contains(verb)) {
    validActions[verb]();
  } else if (invalidActions1.contains(verb) || invalidActions2.contains(verb)) {
    notAllowedInLocMsg(mainWindow, verb);
  } else {
    confusedMsg(mainWindow);
  }
}

void Handling::splitInput(MainWindow *mainWindow, QString input) {
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
  } else {
    handleVerb(mainWindow, verb, target, subject,
               worldObj.getCurrentLocation());
  }
}

// Inputted verb must match an element of argVerbs or noArgVerbs to be
// considered valid
int Handling::validateVerb(QString input) {
  QString inputVerb = input.split(" ").at(0);
  QMap<QString, int> validVerbs{
      {"ASK", VERB_ARG},        {"BEGIN", VERB_NO_ARG},
      {"COOK", VERB_ARG},       {"CRAFT", VERB_ARG},
      {"CRY", VERB_NO_ARG},     {"DIAGNOSE", VERB_NO_ARG},
      {"DRINK", VERB_ARG},      {"DROP", VERB_ARG},
      {"E", VERB_NO_ARG},       {"EAT", VERB_ARG},
      {"EXAMINE", VERB_ARG},    {"EXIT", VERB_NO_ARG},
      {"FILL", VERB_ARG},       {"GO", VERB_ARG},
      {"GOODBYE", VERB_NO_ARG}, {"GREET", VERB_NO_ARG},
      {"HELP", VERB_NO_ARG},    {"HUNT", VERB_ARG},
      {"L", VERB_ARG},          {"LOAD", VERB_ARG},
      {"LOOK", VERB_ARG},       {"MOVE", VERB_ARG},
      {"N", VERB_NO_ARG},       {"PUT", VERB_ARG},
      {"Q", VERB_NO_ARG},       {"QUIT", VERB_NO_ARG},
      {"R", VERB_NO_ARG},       {"READ", VERB_ARG},
      {"REFLECT", VERB_NO_ARG}, {"REMOVE", VERB_ARG},
      {"S", VERB_NO_ARG},       {"SCREAM", VERB_NO_ARG},
      {"SCRIPT", VERB_NO_ARG},  {"SHOOT", VERB_ARG},
      {"SHOUT", VERB_NO_ARG},   {"SIT", VERB_ARG},
      {"SKIN", VERB_ARG},       {"SLEEP", VERB_NO_ARG},
      {"STAND", VERB_ARG},      {"TAKE", VERB_ARG},
      {"TELL", VERB_ARG},       {"UNSCRIPT", VERB_NO_ARG},
      {"USE", VERB_ARG},        {"VERSION", VERB_NO_ARG},
      {"W", VERB_NO_ARG},       {"WAIT", VERB_NO_ARG},
      {"WEAR", VERB_ARG},       {"X", VERB_NO_ARG},
      {"YELL", VERB_NO_ARG},    {"Z", VERB_NO_ARG}};
  if (validVerbs.contains(inputVerb)) {
    return validVerbs.value(inputVerb);
  } else {
    return VERB_INVALID;
  }
}

void Handling::initFillerWords(const QStringList &words) {
  QString pattern = QString("\\b(%1)\\b").arg(words.join("|"));
  fillerWordsRegex = QRegularExpression(pattern);
}

QString Handling::removeFillerWords(const QString &text) {
  QString modifiedText = text;
  modifiedText.remove(fillerWordsRegex);
  return modifiedText.trimmed().replace(multiSpaces, " ");
}

void Handling::gameOverMsg(MainWindow *mainWindow, QString reason) {
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

void Handling::characterNotActiveMsg(MainWindow *mainWindow, QString target) {
  mainWindow->setDescription(
      QString("I didn't see anyone by the description of %1 in the area.")
          .arg(target.toLower()));
}

void Handling::confusedMsg(MainWindow *mainWindow) {
  mainWindow->setDescription(
      "My thoughts were pushing me in a nonsensical direction.");
}

void Handling::invalidTopicMsg(MainWindow *mainWindow) {
  mainWindow->setDescription("It didn't seem like an appropriate topic.");
}
void Handling::missingItemMsg(MainWindow *mainWindow, QString target) {
  mainWindow->setDescription(
      QString("I didn't have %1.").arg(target.toLower()));
}

void Handling::notAllowedDirMsg(MainWindow *mainWindow, QString verb,
                                QString target) {
  mainWindow->setDescription(
      QString("I couldn't %1 %2 there.").arg(verb.toLower(), target.toLower()));
}

void Handling::notAllowedInLocMsg(MainWindow *mainWindow, QString action) {
  mainWindow->setDescription(
      QString("I couldn't %1 there.").arg(action.toLower()));
}

void Handling::notGreetedMsg(MainWindow *mainWindow) {
  mainWindow->setDescription(
      "I should greet someone before trying to have a conversation.");
}

void Handling::tiredMsg(MainWindow *mainWindow) {
  mainWindow->setDescription(
      "I didn't have the energy to travel anywhere else that day.\n");
}

void Handling::waitMsg(MainWindow *mainWindow) {
  mainWindow->setDescription("I waited a while.");
}

QRegularExpression Handling::fillerWordsRegex;

const QRegularExpression Handling::multiSpaces(R"(\s+)");

Handling handlingObj;

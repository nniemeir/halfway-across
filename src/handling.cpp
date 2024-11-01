#include "../include/handling.h"
#include "../include/world.h"
#include <QDebug>

Handling::Handling() {

  argVerbs = {"ASK",  "COOK", "CRAFT",  "DRINK", "DROP", "EAT",  "EXAMINE",
              "FILL", "GO",   "HUNT",   "L",     "LOAD", "LOOK", "MOVE",
              "PUT",  "READ", "REMOVE", "SHOOT", "SIT",  "SKIN", "STAND",
              "TAKE", "TELL", "USE",    "WEAR"};

  noArgVerbs = {"BEGIN",  "CRY",   "DIAGNOSE", "E",        "HELP",    "N",
                "Q",      "QUIT",  "R",        "REFLECT",  "S",       "SCREAM",
                "SCRIPT", "SHOUT", "SLEEP",    "UNSCRIPT", "VERSION", "W",
                "WAIT",   "X",     "YELL",     "Z"};

  fillerWords = {"A", "AN", "AT", "COOKED", "FROM", "IN", "THE", "TO"};
}

Handling handlingObj;

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
  if (verb == "Q" || verb == "QUIT") {
    mainWindow->closeProgram();
  }

  else {
    QMap<QString, std::function<void()>> gameplayActions;
    QMap<QString, std::function<void()>> menuActions;
    gameplayActions["ASK"] = [mainWindow, target, subject, location, this]() {
      ask(mainWindow, target, subject, location);
    };
    gameplayActions["COOK"] = [mainWindow, target, location, this]() {
      cook(mainWindow, target, location);
    };
    gameplayActions["CRAFT"] = [mainWindow, target, this]() {
      craft(mainWindow, target);
    };
    gameplayActions["CRY"] = [mainWindow, this]() { cry(mainWindow); };
    gameplayActions["DIAGNOSE"] = [mainWindow, location, this]() {
      diagnose(mainWindow, location);
    };
    gameplayActions["DRINK"] = [mainWindow, target, location, this]() {
      drink(mainWindow, target, location);
    };
    gameplayActions["DROP"] = [mainWindow, target, subject, location, this]() {
      put(mainWindow, target, "GROUND", location);
    };
    gameplayActions["E"] = [mainWindow, verb, location, this]() {
      move(mainWindow, verb, location);
    };
    gameplayActions["EAT"] = [mainWindow, target, this]() {
      eat(mainWindow, target);
    };
    gameplayActions["EXAMINE"] = [mainWindow, target, location, this]() {
      examine(mainWindow, target);
    };
    gameplayActions["FILL"] = [mainWindow, target, location, this]() {
      fill(mainWindow, target, location);
    };
    gameplayActions["GO"] = [mainWindow, target, location, this]() {
      move(mainWindow, target, location);
    };
    gameplayActions["HELP"] = [mainWindow, target, this]() {
      help(mainWindow);
    };
    gameplayActions["HUNT"] = [mainWindow, target, location, this]() {
      hunt(mainWindow, target, location);
    };
    gameplayActions["L"] = [mainWindow, target, location, this]() {
      look(mainWindow, target, location);
    };
    gameplayActions["LOAD"] = [mainWindow, target, this]() {
      load(mainWindow, target);
    };
    gameplayActions["LOOK"] = [mainWindow, target, location, this]() {
      look(mainWindow, target, location);
    };
    gameplayActions["MOVE"] = [mainWindow, target, location, this]() {
      move(mainWindow, target, location);
    };
    gameplayActions["N"] = [mainWindow, verb, location, this]() {
      move(mainWindow, verb, location);
    };
    gameplayActions["PUT"] = [mainWindow, target, subject, location, this]() {
      put(mainWindow, target, subject, location);
    };
    gameplayActions["READ"] = [mainWindow, location, target, this]() {
      read(mainWindow, location, target);
    };
    gameplayActions["R"] = [mainWindow, location, this]() {
      diagnose(mainWindow, location);
    };
    gameplayActions["REFLECT"] = [mainWindow, location, this]() {
      diagnose(mainWindow, location);
    };
    gameplayActions["REMOVE"] = [mainWindow, target, this]() {
      remove(mainWindow, target);
    };
    gameplayActions["S"] = [mainWindow, verb, location, this]() {
      move(mainWindow, verb, location);
    };
    gameplayActions["SCREAM"] = [mainWindow, location, this]() {
      yell(mainWindow, location);
    };
    gameplayActions["SCRIPT"] = [mainWindow, this]() { script(mainWindow); };
    gameplayActions["SHOOT"] = [mainWindow, target, location, this]() {
      shoot(mainWindow, target, location);
    };
    gameplayActions["SHOUT"] = [mainWindow, location, this]() {
      yell(mainWindow, location);
    };
    gameplayActions["SIT"] = [mainWindow, target, location, this]() {
      sit(mainWindow, target, location);
    };
    gameplayActions["SKIN"] = [mainWindow, target, location, this]() {
      skin(mainWindow, target, location);
    };
    gameplayActions["SLEEP"] = [mainWindow, location, this]() {
      sleep(mainWindow, location);
    };
    gameplayActions["STAND"] = [mainWindow, this]() { stand(mainWindow); };
    gameplayActions["TAKE"] = [mainWindow, target, location, this]() {
      take(mainWindow, target, location);
    };
    gameplayActions["TELL"] = [mainWindow, target, subject, location, this]() {
      tell(mainWindow, target, subject, location);
    };
    gameplayActions["UNSCRIPT"] = [mainWindow, this]() {
      unscript(mainWindow);
    };
    gameplayActions["USE"] = [mainWindow, target, location, this]() {
      use(mainWindow, target, location);
    };
    gameplayActions["VERSION"] = [mainWindow, this]() { version(mainWindow); };
    gameplayActions["W"] = [mainWindow, verb, location, this]() {
      move(mainWindow, verb, location);
    };
    gameplayActions["WAIT"] = [mainWindow, location, this]() {
      wait(mainWindow, location);
    };
    gameplayActions["WEAR"] = [mainWindow, target, this]() {
      wear(mainWindow, target);
    };
    gameplayActions["X"] = [mainWindow, target, location, this]() {
      examine(mainWindow, target);
    };
    gameplayActions["YELL"] = [mainWindow, location, this]() {
      yell(mainWindow, location);
    };
    gameplayActions["Z"] = [mainWindow, location, this]() {
      wait(mainWindow, location);
    };
    menuActions["BEGIN"] = [mainWindow, location, this]() {
      begin(mainWindow, location);
    };
    menuActions["HELP"] = [mainWindow, this]() { help(mainWindow); };

    if (location->getName() == "Perished Menu" ||
        location->getName() == "Introduction Menu") {
      handleVerbActions(mainWindow, verb, target, subject, location,
                        menuActions, gameplayActions);
    } else {
      handleVerbActions(mainWindow, verb, target, subject, location,
                        gameplayActions, menuActions);
    }
  }
}

void Handling::handleVerbActions(
    MainWindow *mainWindow, QString verb, QString target, QString subject,
    Location *location, QMap<QString, std::function<void()>> validActions,
    QMap<QString, std::function<void()>> invalidActions) {
  if (validActions.contains(verb)) {
    validActions[verb]();
  } else if (invalidActions.contains(verb)) {
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
  initFillerWords(fillerWords);
  bool validArgVerb = false;
  bool validNoArgVerb = false;
  QString inputVerb = input.split(" ").at(0);
  if (std::find(argVerbs.begin(), argVerbs.end(), inputVerb) !=
      argVerbs.end()) {
    return 0;
  }
  if (std::find(noArgVerbs.begin(), noArgVerbs.end(), inputVerb) !=
      noArgVerbs.end()) {
    return 1;
  }
  return -1;
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

void Handling::tiredMsg(MainWindow *mainWindow) {
  mainWindow->setDescription(
      "I didn't have the energy to travel anywhere else that day.\n");
}

void Handling::waitMsg(MainWindow *mainWindow) {
  mainWindow->setDescription("I waited a while.");
}

QRegularExpression Handling::fillerWordsRegex;

const QRegularExpression Handling::multiSpaces(R"(\s+)");

#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/world.h"
#include <QRegularExpression>

handling::handling() {

    argVerbs = {
                                              "COOK",  "CHISEL", "DRINK", "DROP",  "EAT",    "EXAMINE",
                                              "GO",    "LOOK",   "MOVE",  "OPEN",  "REMOVE", "SIT",
                                              "STAND", "TAKE",   "TELL",  "THROW", "USE",    "WEAR"};

   noArgVerbs = {"BEGIN", "QUIT", "REFLECT",
                                                   "SLEEP", "WAIT", "Z"};
}

handling handle;

QString handling::removeWords(const QString& text, const QStringList& words) {
    QString pattern = QString("\\b(%1)\\b").arg(words.join("|"));
    QRegularExpression regex(pattern);
    QString modifiedText = text;
    modifiedText.remove(regex);
    return modifiedText.trimmed().replace(QRegularExpression("\\s+"), " ");
}

// Inputted verb must match an element of argVerbs or noArgVerbs to be
// considered valid
int handling::validateVerb(QString input) {
  bool validArgVerb = false;
  bool validNoArgVerb = false;
  QString inputVerb = input.split(" ").at(0);

  if (std::find(argVerbs.begin(), argVerbs.end(), inputVerb) != argVerbs.end()) {
      return 0;
  }
  if (std::find(noArgVerbs.begin(), noArgVerbs.end(), inputVerb) != noArgVerbs.end()) {
      return 1;
  }
  return -1;
}

void handling::splitInput(MainWindow *mainWindow, QString input) {
QStringList fillerWords = {"AT", "IN", "ON", "THE"};
    input = removeWords(input, fillerWords);

  QStringList parts = input.split(" ");

  QString verb;
  QString target;

  if (!parts.isEmpty()) {
    verb = parts.at(0);

    if (parts.size() > 1) {
      target = parts.mid(1).join(" ");
    }
  }
  if (target == "") {
    mainWindow->setDescription(
        QString("You don't know what to %1.").arg(verb.toLower()));
  }
  handle.handleVerb(mainWindow, verb, target, world.getCurrentLocation());
}

void handling::handleVerb(MainWindow *mainWindow, QString verb, QString target,
                          Location *location) {
  if (verb == "BEGIN") {
    handling::begin(mainWindow, location);
  } else if (verb == "COOK") {
    handling::cook(mainWindow, target, location);
  } else if (verb == "DRINK") {
    handling::drink(mainWindow, target, location);
  } else if (verb == "DROP") {
    handling::drop(mainWindow, target, location);
  } else if (verb == "EAT") {
    handling::eat(mainWindow, target);
  } else if (verb == "EXAMINE" || verb == "LOOK") {
    handling::look(mainWindow, target, location);
  } else if (verb == "GO" || verb == "MOVE") {
    handling::move(mainWindow, target, location);
  } else if (verb == "QUIT") {
    mainWindow->closeProgram();
  } else if (verb == "REFLECT") {
    mainWindow->setDescription(player.constructReflection());
  } else if (verb == "REMOVE") {
    handling::remove(mainWindow, target);
  } else if (verb == "SIT") {
    handling::sit(mainWindow, target, location);
  } else if (verb == "SLEEP") {
    handling::sleep(mainWindow, location);
  } else if (verb == "STAND") {
    handling::stand(mainWindow);
  } else if (verb == "TAKE") {
    handling::take(mainWindow, target, location);
  } else if (verb == "USE") {
    handling::use(mainWindow, target, location);
  } else if (verb == "WAIT" || verb == "Z") {
    handling::wait(mainWindow, location);
  } else if (verb == "WEAR") {
    handling::wear(mainWindow, target);
  } else {
    mainWindow->setDescription(
        QString("You can't %1 here.").arg(verb.toLower()));
  }
}

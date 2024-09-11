#include "../include/handling.h"
#include "../include/player.h"
#include "../include/world.h"
#include <QRegularExpression>

Handling::Handling() {

    argVerbs = {
                                              "COOK",  "CHISEL", "DRINK", "DROP",  "EAT",    "EXAMINE",
                                              "GO",    "LOOK",   "MOVE",  "OPEN",  "REMOVE", "SIT",
                                              "STAND", "TAKE",   "TELL",  "THROW", "USE",    "WEAR"};

   noArgVerbs = {"BEGIN", "QUIT", "REFLECT",
                                                   "SLEEP", "WAIT", "Z"};
}

Handling handle;

// Inputted verb must match an element of argVerbs or noArgVerbs to be
// considered valid
int Handling::validateVerb(QString input) {
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

void Handling::splitInput(MainWindow *mainWindow, QString input) {
QStringList fillerWords = {"A", "AT", "IN", "ON", "THE", "TO"};
    input = removeFillerWords(input, fillerWords);

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
  handleVerb(mainWindow, verb, target, world.getCurrentLocation());
}

void Handling::handleVerb(MainWindow *mainWindow, QString verb, QString target,
                          Location *location) {
    QMap<QString, std::function<void()>> actions;
    actions["BEGIN"] = [mainWindow, location, this]() { begin(mainWindow, location); };
    actions["COOK"] = [mainWindow, target, location, this]() { cook(mainWindow, target, location); };
    actions["DRINK"] = [mainWindow, target, location, this]() { drink(mainWindow, target, location); };
    actions["DROP"] = [mainWindow, target, location, this]() { drop(mainWindow, target, location); };
    actions["EAT"] = [mainWindow, target, this]() { eat(mainWindow, target); };
    actions["EXAMINE"] = [mainWindow, target, location, this]() { look(mainWindow, target, location); };
    actions["GO"] = [mainWindow, target, location, this]() { move(mainWindow, target, location); };
    actions["LOOK"] = [mainWindow, target, location, this]() { look(mainWindow, target, location); };
    actions["MOVE"] = [mainWindow, target, location, this]() { move(mainWindow, target, location); };
    actions["QUIT"] = [mainWindow, this]() {     mainWindow->closeProgram(); };
    actions["REFLECT"] = [mainWindow, this]() {     mainWindow->setDescription(player.constructReflection()); };
    actions["REMOVE"] = [mainWindow, target, this]() {     remove(mainWindow, target); };
    actions["SIT"] = [mainWindow, target, location, this]() {     sit(mainWindow, target, location); };
    actions["SLEEP"] = [mainWindow, location, this]() {     sleep(mainWindow, location); };
    actions["STAND"] = [mainWindow, this]() {     stand(mainWindow); };
    actions["TAKE"] = [mainWindow, target, location, this]() {     take(mainWindow, target, location); };
    actions["USE"] = [mainWindow, target, location, this]() {     use(mainWindow, target, location); };
    actions["WAIT"] = [mainWindow, location, this]() {     wait(mainWindow, location); };
    actions["WEAR"] = [mainWindow, target, this]() {     wear(mainWindow, target); };
    actions["Z"] = [mainWindow, location, this]() {     wait(mainWindow, location); };

    if (actions.contains(verb)) {
        actions[verb]();
    } else {
        mainWindow->setDescription(QString("You don't know how to %1.").arg(verb.toLower()));
    }
}

QString Handling::removeFillerWords(const QString& text, const QStringList& words) {
    QString pattern = QString("\\b(%1)\\b").arg(words.join("|"));
    QRegularExpression regex(pattern);
    QString modifiedText = text;
    modifiedText.remove(regex);
    return modifiedText.trimmed().replace(QRegularExpression("\\s+"), " ");
}

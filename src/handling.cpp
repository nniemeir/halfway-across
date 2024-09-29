#include "../include/handling.h"
#include "../include/hunting.h"
#include "../include/player.h"
#include "../include/world.h"

Handling::Handling()
{

  argVerbs = {"COOK", "CRAFT", "DRINK", "DROP", "EAT", "EXAMINE", "GO",
              "HUNT", "L", "LOAD", "LOOK", "MOVE", "READ", "REMOVE",
              "SHOOT", "SIT", "SKIN", "STAND", "TAKE", "USE", "WEAR"};

  noArgVerbs = {"BEGIN", "CRY", "E", "HELP", "N",
                "Q", "QUIT", "REFLECT", "S", "SCREAM",
                "SCRIPT", "SHOUT", "SLEEP", "UNSCRIPT", "VERSION",
                "W", "WAIT", "X", "YELL", "Z"};
}

Handling handle;

QString Handling::getArticle(QString target)
{
  QStringList vowels = {"A", "E", "I", "O", "U"};
  QString firstLetter = target.at(0).toUpper();
  if (vowels.contains(firstLetter))
  {
    return "an";
  }
  else
  {
    return "a";
  }
}

// Inputted verb must match an element of argVerbs or noArgVerbs to be
// considered valid
int Handling::validateVerb(QString input)
{
  bool validArgVerb = false;
  bool validNoArgVerb = false;
  QString inputVerb = input.split(" ").at(0);
  if (std::find(argVerbs.begin(), argVerbs.end(), inputVerb) !=
      argVerbs.end())
  {
    return 0;
  }
  if (std::find(noArgVerbs.begin(), noArgVerbs.end(), inputVerb) !=
      noArgVerbs.end())
  {
    return 1;
  }
  return -1;
}

void Handling::splitInput(MainWindow *mainWindow, QString input)
{
  QStringList fillerWords = {"A", "AN", "AT", "COOKED", "FROM",
                             "IN", "ON", "THE", "TO"};
  input = removeFillerWords(input, fillerWords);

  QStringList parts = input.split(" ");

  QString verb;
  QString target;

  if (!parts.isEmpty())
  {
    verb = parts.at(0);

    if (parts.size() > 1)
    {
      target = parts.mid(1).join(" ");
    }
  }
  if (target == "")
  {
    mainWindow->setDescription(
        QString("I didn't know what to %1.").arg(verb.toLower()));
  }
  else
  {
    handleVerb(mainWindow, verb, target, world.getCurrentLocation());
  }
}

void Handling::handleVerb(MainWindow *mainWindow, QString verb, QString target,
                          Location *location)
{
  QMap<QString, std::function<void()>> actions;
  // The handling for the verb "AGAIN" is located in
  // MainWindow::handleReturnPressed
  actions["BEGIN"] = [mainWindow, location, this]()
  {
    begin(mainWindow, location);
  };
  actions["COOK"] = [mainWindow, target, location, this]()
  {
    cook(mainWindow, target, location);
  };
  actions["CRAFT"] = [mainWindow, target, this]()
  {
    craft(mainWindow, target);
  };
  actions["CRY"] = [mainWindow, this]()
  { cry(mainWindow); };
  actions["DRINK"] = [mainWindow, target, location, this]()
  {
    drink(mainWindow, target, location);
  };
  actions["DROP"] = [mainWindow, target, location, this]()
  {
    drop(mainWindow, target, location);
  };
  actions["E"] = [mainWindow, verb, location, this]()
  {
    move(mainWindow, verb, location);
  };
  actions["EAT"] = [mainWindow, target, this]()
  { eat(mainWindow, target); };
  actions["EXAMINE"] = [mainWindow, target, location, this]()
  {
    examine(mainWindow, target);
  };
  actions["GO"] = [mainWindow, target, location, this]()
  {
    move(mainWindow, target, location);
  };
  actions["HELP"] = [mainWindow, target, this]()
  { help(mainWindow); };
  actions["HUNT"] = [mainWindow, target, location, this]()
  {
    hunting.hunt(mainWindow, target, location);
  };
  actions["L"] = [mainWindow, target, location, this]()
  {
    look(mainWindow, target, location);
  };
  actions["LOAD"] = [mainWindow, target, this]()
  { load(mainWindow, target); };
  actions["LOOK"] = [mainWindow, target, location, this]()
  {
    look(mainWindow, target, location);
  };
  actions["MOVE"] = [mainWindow, target, location, this]()
  {
    move(mainWindow, target, location);
  };
  actions["N"] = [mainWindow, verb, location, this]()
  {
    move(mainWindow, verb, location);
  };
  actions["Q"] = [mainWindow, this]()
  { mainWindow->closeProgram(); };
  actions["QUIT"] = [mainWindow, this]()
  { mainWindow->closeProgram(); };
  actions["READ"] = [mainWindow, target, this]()
  { read(mainWindow, target); };
  actions["REFLECT"] = [mainWindow, this]()
  {
    mainWindow->setDescription(player.constructReflection());
  };
  actions["REMOVE"] = [mainWindow, target, this]()
  {
    remove(mainWindow, target);
  };
  actions["S"] = [mainWindow, verb, location, this]()
  {
    move(mainWindow, verb, location);
  };
  actions["SCREAM"] = [mainWindow, this]()
  { yell(mainWindow); };
  actions["SCRIPT"] = [mainWindow, this]()
  { script(mainWindow); };
  actions["SHOOT"] = [mainWindow, target, location, this]()
  { shoot(mainWindow, target, location); };
  actions["SHOUT"] = [mainWindow, this]()
  { yell(mainWindow); };
  actions["SIT"] = [mainWindow, target, location, this]()
  {
    sit(mainWindow, target, location);
  };
  actions["SKIN"] = [mainWindow, target, location, this]()
  {
    skin(mainWindow, target, location);
  };
  actions["SLEEP"] = [mainWindow, location, this]()
  {
    sleep(mainWindow, location);
  };
  actions["STAND"] = [mainWindow, this]()
  { stand(mainWindow); };
  actions["TAKE"] = [mainWindow, target, location, this]()
  {
    take(mainWindow, target, location);
  };
  actions["UNSCRIPT"] = [mainWindow, this]()
  { unscript(mainWindow); };
  actions["USE"] = [mainWindow, target, location, this]()
  {
    use(mainWindow, target, location);
  };
  actions["VERSION"] = [mainWindow, this]()
  { version(mainWindow); };
  actions["W"] = [mainWindow, verb, location, this]()
  {
    move(mainWindow, verb, location);
  };
  actions["WAIT"] = [mainWindow, location, this]()
  {
    wait(mainWindow, location);
  };
  actions["WEAR"] = [mainWindow, target, this]()
  { wear(mainWindow, target); };
  actions["X"] = [mainWindow, target, location, this]()
  {
    examine(mainWindow, target);
  };
  actions["YELL"] = [mainWindow, this]()
  { yell(mainWindow); };
  actions["Z"] = [mainWindow, location, this]()
  { wait(mainWindow, location); };

  if (actions.contains(verb))
  {
    actions[verb]();
  }
  else
  {
    mainWindow->setDescription(
        "My thoughts were pushing me in a direction that I didn't understand.");
  }
}

QString Handling::getLastCommand() const { return lastCommand; }
void Handling::setLastCommand(QString command) { lastCommand = command; }

QString Handling::removeFillerWords(const QString &text,
                                    const QStringList &words)
{
  QString pattern = QString("\\b(%1)\\b").arg(words.join("|"));
  QRegularExpression regex(pattern);
  QString modifiedText = text;
  modifiedText.remove(regex);
  return modifiedText.trimmed().replace(QRegularExpression("\\s+"), " ");
}

void Handling::gameOverMsg(MainWindow *mainWindow, QString reason)
{
  QMap<QString, QString> stat = {
      {"HEALTH", "My injuries were too grave for me to continue."},
      {"HUNGER", "I succumbed to my hunger."},
      {"MENTAL", "I had lost the will to continue."},
      {"THIRST", "I succumbed to my thirst."}};

  if (stat.contains(reason))
  {
    mainWindow->setDescription(perished.setDescription(stat.value(reason)));
  }
  else
  {
    qDebug() << "Unable to determine reason for game over.";
  }
  mainWindow->setLocation(world.getCurrentLocation()->getMusicPath(),
                          world.getCurrentLocation()->getAmbiencePath(),
                          &perished);
}

void Handling::missingItemMsg(MainWindow *mainWindow, QString target)
{
  mainWindow->setDescription(
      QString("I didn't have %1.").arg(target.toLower()));
}

void Handling::notAllowedDirMsg(MainWindow *mainWindow, QString verb,
                                QString target)
{
  mainWindow->setDescription(QString("I couldn't %1 %2 there.")
                                 .arg(verb.toLower())
                                 .arg(target.toLower()));
}

void Handling::notAllowedInLocMsg(MainWindow *mainWindow, QString action)
{
  mainWindow->setDescription(
      QString("I couldn't %1 there.").arg(action.toLower()));
}

void Handling::tiredMsg(MainWindow *mainWindow)
{
  mainWindow->setDescription(
      "I didn't have the energy to travel anywhere else that day.\n");
}

void Handling::waitMsg(MainWindow *mainWindow)
{
  mainWindow->setDescription("I waited a while.");
}

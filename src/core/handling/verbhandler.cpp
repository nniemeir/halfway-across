#include "../../../include/core/handling/msghandler.h"
#include "../../../include/core/handling/verbhandler.h"
#include "../../../include/core/world.h"

VerbHandler::VerbHandler() {}

void VerbHandler::handleVerb(MainWindow *mainWindow, QString verb,
                              QString target, QString subject,
                              Location *location) {
  // The handling for the verb "AGAIN" is located in
  // MainWindow::handleReturnPressed
  if (verb == "EXIT" || verb == "Q" || verb == "QUIT") {
    mainWindow->closeProgram();
    return;
  }
  QMap<QString, std::function<void()>> dialogueActions{
      {"ASK", [mainWindow, verb, target, subject, location,
               this]() { talk(mainWindow, verb, target, subject, location); }},
      {"GOODBYE",
       [mainWindow, location, this]() { goodbye(mainWindow, location); }},
      {"TELL", [mainWindow, verb, target, subject, location, this]() {
         talk(mainWindow, verb, target, subject, location);
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
      {"EAST", [mainWindow, verb, location,
             this]() { move(mainWindow, verb, location); }},
      {"EAT", [mainWindow, target, this]() { eat(mainWindow, target); }},
      {"EXAMINE",
       [mainWindow, target, location, this]() { examine(mainWindow, target); }},
      {"FILL", [mainWindow, target, location,
                this]() { fill(mainWindow, target, location); }},
      {"GO", [mainWindow, target, location,
              this]() { move(mainWindow, target, location); }},
      {"GREET", [mainWindow, target, location, this]() { greet(mainWindow); }},
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
      {"NORTH", [mainWindow, verb, location,
                this]() { move(mainWindow, verb, location); }},
      {"PUT", [mainWindow, target, subject, location,
               this]() { put(mainWindow, target, subject, location); }},
      {"READ", [mainWindow, location, target,
                this]() { read(mainWindow, location, target); }},
      {"R", [mainWindow, location, this]() { diagnose(mainWindow, location); }},
      {"REFLECT",
       [mainWindow, location, this]() { diagnose(mainWindow, location); }},
      {"REMOVE", [mainWindow, target, this]() { remove(mainWindow, target); }},
      {"S", [mainWindow, verb, location,
             this]() { move(mainWindow, verb, location); }},
      {"SCREAM",
       [mainWindow, location, this]() { yell(mainWindow, location); }},
      {"SCRIPT", [mainWindow, this]() { script(mainWindow); }},
      {"SHOOT", [mainWindow, target, location,
                 this]() { shoot(mainWindow, target, location); }},
      {"SHOUT", [mainWindow, location, this]() { yell(mainWindow, location); }},
      {"SIT", [mainWindow, target, location,
               this]() { sit(mainWindow, target, location); }},
      {"SKIN", [mainWindow, target, location,
                this]() { skin(mainWindow, target, location); }},
      {"SLEEP",
       [mainWindow, location, this]() { sleep(mainWindow, location); }},
      {"SOUTH", [mainWindow, verb, location,
                this]() { move(mainWindow, verb, location); }},
      {"STAND", [mainWindow, this]() { stand(mainWindow); }},
      {"TAKE", [mainWindow, target, location,
                this]() { take(mainWindow, target, location); }},
      {"UNSCRIPT", [mainWindow, this]() { unscript(mainWindow); }},
      {"USE", [mainWindow, target, location,
               this]() { use(mainWindow, target, location); }},
      {"VERSION", [mainWindow, this]() { version(mainWindow); }},
      {"W", [mainWindow, verb, location,
             this]() { move(mainWindow, verb, location); }},
      {"WAIT", [mainWindow, location, this]() { wait(mainWindow, location); }},
      {"WEAR", [mainWindow, target, this]() { wear(mainWindow, target); }},
      {"WEST", [mainWindow, verb, location,
                this]() { move(mainWindow, verb, location); }},
      {"X",
       [mainWindow, target, location, this]() { examine(mainWindow, target); }},
      {"YELL", [mainWindow, location, this]() { yell(mainWindow, location); }},
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
    handleVerbActions(mainWindow, verb, target, subject, location, menuActions,
                      dialogueActions, gameplayActions);
    return;
  }
  handleVerbActions(mainWindow, verb, target, subject, location,
                    gameplayActions, dialogueActions, menuActions);
}

void VerbHandler::handleVerbActions(
    MainWindow *mainWindow, QString verb, QString target, QString subject,
    Location *location, QMap<QString, std::function<void()>> validActions,
    QMap<QString, std::function<void()>> invalidActions1,
    QMap<QString, std::function<void()>> invalidActions2) {
  if (validActions.contains(verb)) {
    validActions[verb]();
    return;
  }
  if (invalidActions1.contains(verb) || invalidActions2.contains(verb)) {
    msgHandlerObj.notAllowedInLocMsg(mainWindow, verb);
    return;
  }
  msgHandlerObj.confusedMsg(mainWindow);
}

VerbHandler verbHandlerObj;

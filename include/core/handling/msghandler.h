#ifndef MSGHANDLER_H
#define MSGHANDLER_H
#include "../../../include/ui/mainwindow.h"
class MsgHandler {
public:
    MsgHandler();
    void confusedMsg(MainWindow *mainWindow);
    void characterNotActiveMsg(MainWindow *mainWindow, QString target);
    void gameOverMsg(MainWindow *mainWindow, QString reason);
    void invalidTopicMsg(MainWindow *mainWindow);
    void missingItemMsg(MainWindow *mainWindow, QString target);
    void notAllowedDirMsg(MainWindow *mainWindow, QString verb, QString target);
    void notAllowedInLocMsg(MainWindow *mainWindow, QString action);
    void notGreetedMsg(MainWindow *mainWindow);
    void tiredMsg(MainWindow *mainWindow);
    void waitMsg(MainWindow *mainWindow);
};
extern MsgHandler msgHandlerObj;

#endif // MSGHANDLER_H

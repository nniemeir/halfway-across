#include "../../include/handling.h"
#include "../../include/world.h"

void Handling::tell(MainWindow *mainWindow, QString target, QString subject,
                    Location *location) {
  if (worldObj.getActiveCharacter() != nullptr) {
    QMap<QString, std::function<void()>> validCharacters;
    validCharacters["AMOS"] = [mainWindow, subject, location, this]() {
      tellAmos(mainWindow, subject, location);
    };
    validCharacters["IRA"] = [mainWindow, subject, location, this]() {
      tellIra(mainWindow, subject, location);
    };
    if (validCharacters.contains(target)) {
      if (QString::compare(target, worldObj.getActiveCharacter()->getName(),
                           Qt::CaseInsensitive) == 0) {
        validCharacters[target]();
        return;
      }
    }
  }
  characterNotActiveMsg(mainWindow, target);
}

void Handling::tellAmos(MainWindow *mainWindow, QString subject,
                        Location *location) {
  mainWindow->setDescription(
      "Placeholder message for telling Amos about subjects.");
}

void Handling::tellIra(MainWindow *mainWindow, QString subject,
                       Location *location) {
  mainWindow->setDescription(
      "Placeholder message for telling Ira about subjects.");
}

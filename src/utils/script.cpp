#include "../../include/utils/script.h"

bool Script::getStatus() { return Status; }

void Script::setStatus(bool status) { Status = status; }

bool Script::writeFile(const QString &outputText) {
  if (!file.isOpen()) {
    file.open(QIODevice::Append | QIODevice::Text);
  }
  out << outputText;
  out.flush();
  return true;
}

Script scriptObj("script-" + QDate::currentDate().toString("MM-dd-yy") +
                 ".txt");

#include "../include/script.h"
Script scriptObj("script-" + QDate::currentDate().toString("MM-dd-yy") +
                 ".txt");

bool Script::getRecordingStatus() { return recordingStatus; }

void Script::setRecordingStatus(bool status) { recordingStatus = status; }

bool Script::writeFile(const QString &outputText) {
  if (!file.isOpen()) {
    file.open(QIODevice::Append | QIODevice::Text);
  }
  out << outputText;
  out.flush();
  return true;
}

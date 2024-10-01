#include "../include/journal.h"

Journal journalObj("journal-" + QDate::currentDate().toString("MM-dd-yy") +
                   ".txt");

bool Journal::getRecordingStatus() { return recordingStatus; }

void Journal::setRecordingStatus(bool status) { recordingStatus = status; }

bool Journal::writeFile(const QString &outputText) {
  if (!file.isOpen()) {
    qDebug() << "File is not open for writing";
    return false;
  }
  out << outputText;
  return true;
}
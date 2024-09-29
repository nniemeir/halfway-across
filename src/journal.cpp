#include "../include/journal.h"

Journal journal("journal-" + QDate::currentDate().toString("MM-dd-yy") +
                ".txt");

bool Journal::writeFile(const QString &outputText)
{
  if (!file.isOpen())
  {
    qDebug() << "File is not open for writing";
    return false;
  }
  out << outputText;
  return true;
}

bool Journal::getRecordingStatus() { return recordingStatus; }

void Journal::setRecordingStatus(bool status) { recordingStatus = status; }

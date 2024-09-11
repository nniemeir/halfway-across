#include "../include/transcript.h"

Transcript transcript("transcript-" + QDate::currentDate().toString("MM-dd-yy") + ".txt");

bool Transcript::writeFile(const QString &outputText) {
    if (!file.isOpen()) {
        qDebug() << "File is not open for writing";
        return false;
    }
    out << outputText;
    return true;
}

bool Transcript::getRecordingStatus() {
    return recordingStatus;
}

void Transcript::setRecordingStatus(bool status) {
    recordingStatus = status;
}

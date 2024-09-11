#include "../include/transcript.h"

Transcript transcript("transcript.txt");

bool Transcript::writeFile(const QString &outputText) {
    if (!file.isOpen()) {
        qDebug() << "File is not open for writing";
        return false;
    }
    out << outputText;
    return true;
}

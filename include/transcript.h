#ifndef TRANSCRIPT_H
#define TRANSCRIPT_H
#include <qstring.h>
#include<QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
class Transcript {
public:
    Transcript(const QString &filename) : file(filename), out(&file), recordingStatus(false) {
        QDir dir(QDir::homePath() + "/Documents/Halfway Across");
        file.setFileName(dir.path() + "/" + file.fileName());
        if (!dir.exists()) {
            dir.mkpath(QDir::homePath() + "/Documents/Halfway Across");
        }
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            qDebug() << "Unable to open" << filename << "for writing";
        }
    }

    ~Transcript() {
        if (file.isOpen()) {
            file.close();
        }
    }
    bool writeFile(const QString &outputText);
    bool getRecordingStatus();
    void setRecordingStatus(bool status);


private:
    QFile file;
    QTextStream out;
    bool recordingStatus;
};

extern Transcript transcript;
#endif // TRANSCRIPT_H

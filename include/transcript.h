#ifndef TRANSCRIPT_H
#define TRANSCRIPT_H
#include <qstring.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>
class Transcript {
public:
    Transcript(const QString &filename) : file(filename), out(&file) {
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

private:
    QFile file;
    QTextStream out;
};

extern Transcript transcript;
#endif // TRANSCRIPT_H

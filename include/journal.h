#ifndef JOURNAL_H
#define JOURNAL_H
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <qstring.h>
class Transcript {
public:
  Transcript(const QString &filename)
      : file(filename), out(&file), recordingStatus(false) {
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
#endif // JOURNAL_H

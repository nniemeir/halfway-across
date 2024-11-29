#ifndef SCRIPT_H
#define SCRIPT_H
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <qstring.h>

class Script {
public:
  Script(const QString &filename)
      : file(QDir::homePath() + "/Documents/Halfway Across/" + filename),
        out(&file), Status(false) {
    QDir dir(QDir::homePath() + "/Documents/Halfway Across");
    if (!dir.exists() && !dir.mkpath(".")) {
      qDebug() << "Unable to create directory: " << dir.path();
    }
  }
  ~Script() {
    if (file.isOpen()) {
      file.close();
    }
  }
  bool getStatus();
  void setStatus(bool status);
  bool writeFile(const QString &outputText);

private:
  QFile file;
  QTextStream out;
  bool Status;
};

extern Script scriptObj;

#endif

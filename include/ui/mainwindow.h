#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "core/audio.h"
#include "entities/locations.h"
#include <QApplication>
#include <QEvent>
#include <QFile>
#include <QFontDatabase>
#include <QIcon>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMainWindow>
#include <QPixmap>
#include <QtCore>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  // Setters
  void setLocation(QString currentMusic, QString currentAmbience,
                   Location *object);
  void setLocationAudio(QString currentMusic, QString currentAmbience,
                        Location *object);
  void setLocationImage(QString imagePath);
  void setCompassImage(QString imagePath);
  void setDescription(QString text);
  void appendDescription(QString text);

  void playSfx(const QString& filePath);
  void endGame(QString reason);
  void closeProgram();

private:
  Ui::MainWindow *ui;
  void importStylesheet();
  void setUiProperties();
  Audio ambiencePlayer;
  Audio musicPlayer;
  Audio sfxPlayer;

private slots:
  void handleReturnPressed();

protected:
  void showEvent(QShowEvent *event) override;
};

#endif

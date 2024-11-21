#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "locations.h"
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
  void setLocation(QString currentMusic, QString currentAmbience,
                   Location *object);
  void setCompassImage(QString imagePath);
  void setLocationImage(QString imagePath);
  void appendDescription(QString text);
  void setDescription(QString text);
  void closeProgram();

private:
  Ui::MainWindow *ui;
  void importStylesheet();
  void setUiProperties();

private slots:
  void handleReturnPressed();

protected:
  void showEvent(QShowEvent *event) override;
};

#endif

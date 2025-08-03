#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":/images/icon.png"));
  MainWindow w;
  srand(time(NULL));
  w.showFullScreen();

  return a.exec();
}

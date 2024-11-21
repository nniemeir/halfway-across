#include "../include/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":/images/icon.png"));
  MainWindow w;
  srand(time(NULL));
  w.resize(1280, 720);
  w.show();
  return a.exec();
}

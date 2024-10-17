#include "../include/mainwindow.h"
#include "../include/audio.h"
#include "../include/handling.h"
#include "../include/journal.h"
#include "../include/locations.h"
#include "../include/player.h"
#include "../include/world.h"
#include "src/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  importStylesheet();
  QFontDatabase::addApplicationFont(":/fonts/Caveat.ttf");
  setUiProperties();
  setWindowTitle("Halfway Across");
  setLocation("", "", &intro);
}

void MainWindow::importStylesheet() {
  QFile file(":/stylesheets/stylesheet.qss");
  if (!file.open(QFile::ReadOnly)) {
    qWarning() << "Failed to open stylesheet file:" << file.errorString();
    return;
  }
  QString styleSheet = QLatin1String(file.readAll());
  qApp->setStyleSheet(styleSheet);
}

void MainWindow::setUiProperties() {
  ui->outputArea->setReadOnly(true);
  ui->outputArea->setAlignment(Qt::AlignLeft);
  ui->outputArea->setTextInteractionFlags(Qt::NoTextInteraction);
  connect(ui->inputText, &QLineEdit::returnPressed, this,
          &MainWindow::handleReturnPressed);
}

void MainWindow::showEvent(QShowEvent *event) {
  QMainWindow::showEvent(event);

  if (ui->inputText) {
    QTimer::singleShot(0, this, [this]() { ui->inputText->setFocus(); });
  }
}

void MainWindow::setDescription(QString text) {
  ui->outputArea->setText(text);
  if (journalObj.getRecordingStatus()) {
    journalObj.writeFile(QString("%1\n").arg(text));
  }
}

void MainWindow::closeProgram() { QApplication::quit(); }

void MainWindow::setLocation(QString currentMusic, QString currentAmbience,
                             Location *object) {
  if (object) {
    int rodIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), "FISHING ROD");
    if (rodIndex != -1) {
      inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
          .setActive(0);
    }
    setDescription(object->getDescription());
    QPixmap pix(object->getImage());
    ui->settingImage->setPixmap(pix);
    QString musicPath = object->getMusicPath();
    QString ambiencePath = object->getAmbiencePath();
    if (currentMusic != musicPath) {
      musicPlayer.play(musicPath, ambiencePlayer.getdefMusicVol(), 1);
    }
    if (currentAmbience != ambiencePath) {
      ambiencePlayer.play(ambiencePath, ambiencePlayer.getdefAmbienceVol(), 1);
    }
    worldObj.setCurrentLocation(object);
  }
}

void MainWindow::handleReturnPressed() {
  QString input = ui->inputText->text();
  input = input.toUpper().trimmed();
  if (input == "G" || input == "AGAIN") {
    input = handlingObj.getLastCommand();
  }
  handlingObj.setLastCommand(input);
  if (journalObj.getRecordingStatus()) {
    journalObj.writeFile(QString("> %1\n").arg(input));
  }
  int validated = handlingObj.validateVerb(input);
  if (validated == 0) {
    handlingObj.splitInput(this, input);
  } else if (validated == 1) {
    handlingObj.handleVerb(this, input, "", "", worldObj.getCurrentLocation());
  } else {
    if (input != "") {
      setDescription(QString("I didn't know how to %1.").arg(input.toLower()));
    } else {
      setDescription("I felt confused for a moment.");
    }
  }
  ui->inputText->clear();
}

MainWindow::~MainWindow() { delete ui; }

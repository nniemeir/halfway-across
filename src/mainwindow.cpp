#include "../include/mainwindow.h"
#include "../include/audio.h"
#include "../include/handling.h"
#include "../include/locations.h"
#include "../include/player.h"
#include "../include/script.h"
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

void MainWindow::appendDescription(QString text) {
  ui->outputArea->append(text);
  if (scriptObj.getRecordingStatus()) {
    scriptObj.writeFile(QString("%1\n").arg(text));
  }
}

void MainWindow::setDescription(QString text) {
  ui->outputArea->setText(text);
  if (scriptObj.getRecordingStatus()) {
    scriptObj.writeFile(QString("%1\n").arg(text));
  }
}

void MainWindow::closeProgram() { QApplication::quit(); }

void MainWindow::setCompassImage(QString imagePath) {
  QPixmap pix(imagePath);
  ui->compass->setPixmap(pix);
}

void MainWindow::setLocationImage(QString imagePath) {
  QPixmap pix(imagePath);
  ui->location->setPixmap(pix);
}

void MainWindow::setLocation(QString currentMusic, QString currentAmbience,
                             Location *object) {
  if (object) {
    int rodIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), "FISHING ROD");
    if (rodIndex != Handling::ITEM_NOT_FOUND) {
      inventoryObj.getInventoryItem(playerObj.getInventory(), rodIndex)
          .setActive(false);
    }
    setDescription(object->getDescription());
    setCompassImage(object->getCompass());
    setLocationImage(object->getImage());
    QString musicPath = object->getMusicPath();
    QString ambiencePath = object->getAmbiencePath();
    if (currentMusic != musicPath) {
      musicPlayer.play(musicPath, ambiencePlayer.getdefMusicVol(), true);
    }
    if (currentAmbience != ambiencePath) {
      ambiencePlayer.play(ambiencePath, ambiencePlayer.getdefAmbienceVol(),
                          true);
    }
    worldObj.setCurrentLocation(object);
    if (worldObj.getActiveCharacter() != nullptr &&
        worldObj.getCurrentLocation()->getName() ==
            worldObj.getActiveCharacter()->getLocation()) {
      appendDescription(worldObj.getActiveCharacter()->getBrief());
      if (worldObj.getDay() == 8) {
        appendDescription(
            "\nHint: I can start a conversation by using the command GREET.");
      }
    }
  }
}

void MainWindow::handleReturnPressed() {
  QString input = ui->inputText->text();
  if (input == "") {
    return;
  }
  input = input.toUpper().trimmed();
  if (input == "G" || input == "AGAIN") {
    input = handlingObj.getLastCommand();
  }
  handlingObj.setLastCommand(input);
  if (scriptObj.getRecordingStatus()) {
    scriptObj.writeFile(QString("> %1\n").arg(input));
  }
  int validated = handlingObj.validateVerb(input);
  if (validated == Handling::VERB_ARG) {
    handlingObj.splitInput(this, input);
  } else if (validated == Handling::VERB_NO_ARG) {
    handlingObj.handleVerb(this, input, "", "", worldObj.getCurrentLocation());
  } else {
    if (input != "") {
      setDescription(QString("I didn't know how to %1.").arg(input.toLower()));
    } else {
      handlingObj.confusedMsg(this);
    }
  }
  ui->inputText->clear();
}

MainWindow::~MainWindow() { delete ui; }

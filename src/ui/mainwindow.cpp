#include "../../include/ui/mainwindow.h"
#include "../../include/core/audio.h"
#include "../../include/core/handling/inputhandler.h"
#include "../../include/core/handling/msghandler.h"
#include "../../include/core/handling/verbhandler.h"
#include "../../include/core/world.h"
#include "../../include/entities/locations.h"
#include "../../include/utils/script.h"
#include "src/ui/ui_mainwindow.h"

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

void MainWindow::setCompassImage(QString imagePath) {
  QPixmap pix(imagePath);
  ui->compassPath->setPixmap(pix);
}

void MainWindow::setLocation(QString currentMusic, QString currentAmbience,
                             Location *object) {
  inventoryObj.deactivateLocationSpecificItems();
  setDescription(object->getDescription());
  setCompassImage(object->getCompassPath());
  setLocationImage(object->getImagePath());
  setLocationAudio(currentMusic, currentAmbience, object);
  worldObj.setCurrentLocation(object);
  QString activeCharacterBrief = worldObj.getActiveCharacterBrief();
  if (!activeCharacterBrief.isEmpty()) {
    appendDescription(activeCharacterBrief);
  }
}

void MainWindow::setLocationAudio(QString currentMusic, QString currentAmbience,
                                  Location *object) {
  QString musicPath = object->getMusicPath();
  QString ambiencePath = object->getAmbiencePath();
  if (currentMusic != musicPath) {
    musicPlayer.play(musicPath, ambiencePlayer.getdefMusicVol(), true);
  }
  if (currentAmbience != ambiencePath) {
    ambiencePlayer.play(ambiencePath, ambiencePlayer.getdefAmbienceVol(), true);
  }
}

void MainWindow::setLocationImage(QString imagePath) {
  QPixmap pix(imagePath);
  ui->location->setPixmap(pix);
}

void MainWindow::setDescription(QString text) {
  ui->outputArea->setText(text);
  if (scriptObj.getStatus()) {
    scriptObj.writeFile(QString("%1\n").arg(text));
  }
}

void MainWindow::appendDescription(QString text) {
  ui->outputArea->append(text);
  if (scriptObj.getStatus()) {
    scriptObj.writeFile(QString("%1\n").arg(text));
  }
}

void MainWindow::endGame(QString reason) {
  msgHandlerObj.gameOver(reason);
  this->setLocation(worldObj.getCurrentLocation()->getMusicPath(),
                    worldObj.getCurrentLocation()->getAmbiencePath(),
                    &perished);
  sfxPlayer.play("qrc:/audio/sfx/perished.mp3", sfxPlayer.getdefSfxVol(),
                 false);
};

void MainWindow::closeProgram() { QApplication::quit(); }

void MainWindow::handleReturnPressed() {
  QString input = ui->inputText->text();
  if (input.isEmpty()) {
    return;
  }
  input = input.toUpper().trimmed();
  if (input == "G" || input == "AGAIN") {
    input = inputHandlerObj.getLastCommand();
  }
  inputHandlerObj.setLastCommand(input);
  if (scriptObj.getStatus()) {
    scriptObj.writeFile(QString("> %1\n").arg(input));
  }
  int validated = inputHandlerObj.getVerbType(input);
  if (validated == InputHandler::VERB_ARG) {
    inputHandlerObj.parse(this, input);
    ui->inputText->clear();
    return;
  }
  if (validated == InputHandler::VERB_NO_ARG) {
    verbHandlerObj.process(this, input, "", "", worldObj.getCurrentLocation());
    ui->inputText->clear();
    return;
  }
  if (!input.isEmpty()) {
    setDescription(QString("I didn't know how to %1.").arg(input.toLower()));
    ui->inputText->clear();
    return;
  }
}

MainWindow::~MainWindow() { delete ui; }
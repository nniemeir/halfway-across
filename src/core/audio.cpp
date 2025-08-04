#include "core/audio.h"

Audio::Audio() {
  QObject *audioParent = new QObject();
  music = new QMediaPlayer(audioParent);
  audioOutput = new QAudioOutput(audioParent);
  ambienceVol = 0.8;
  musicVol = 0.9;
  sfxVol = 1;
}

float Audio::getAmbienceVol() const { return ambienceVol; }

float Audio::getMusicVol() const { return musicVol; }

float Audio::getSfxVol() const { return sfxVol; }

void Audio::play(QString filePath, int volume, bool isBackground) {
  if (music->playbackState() == QMediaPlayer::PlayingState) {
    music->stop();
  }
  music->setAudioOutput(audioOutput);
  music->setSource(QUrl(filePath));
  audioOutput->setVolume(1);
  if (isBackground) {
    music->setLoops(QMediaPlayer::Infinite);
  }
  music->play();
}

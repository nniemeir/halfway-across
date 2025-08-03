#include "core/audio.h"

Audio::Audio() {
  QObject *audioParent = new QObject();
  music = new QMediaPlayer(audioParent);
  audioOutput = new QAudioOutput(audioParent);
  defAmbienceVol = 0.8;
  defMusicVol = 0.9;
  defSfxVol = 1;
}

float Audio::getdefAmbienceVol() const { return defAmbienceVol; }

float Audio::getdefMusicVol() const { return defMusicVol; }

float Audio::getdefSfxVol() const { return defSfxVol; }

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

#include "../include/audio.h"

audio::audio() {
  music = new QMediaPlayer();
  audioOutput = new QAudioOutput();
  defAmbienceVol = 0.8;
  defMusicVol = 0.9;
  defSfxVol = 1;
}

void audio::play(QString filePath, int volume, int isBackground) {
  if (music->playbackState() == QMediaPlayer::PlayingState) {
    music->stop();
  }
  music->setAudioOutput(audioOutput);
  music->setSource(QUrl(filePath));
  audioOutput->setVolume(1);
  if (isBackground == 1) {
    music->setLoops(QMediaPlayer::Infinite);
  }
  music->play();
}

float audio::getdefAmbienceVol() const {
    return defAmbienceVol;
}

float audio::getdefMusicVol() const {
    return defMusicVol;
}

float audio::getdefSfxVol() const {
    return defSfxVol;
}

audio ambiencePlayer;
audio musicPlayer;
audio sfxPlayer;

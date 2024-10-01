#ifndef AUDIO_H
#define AUDIO_H
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QUrl>
class Audio {
public:
  Audio();
  float getdefAmbienceVol() const;
  float getdefMusicVol() const;
  float getdefSfxVol() const;
  void play(QString filePath, int volume, int isBackground);

private:
  float defAmbienceVol;
  float defMusicVol;
  float defSfxVol;
  QAudioOutput *audioOutput;
  QMediaPlayer *music;
};

extern Audio ambiencePlayer;
extern Audio musicPlayer;
extern Audio sfxPlayer;

#endif

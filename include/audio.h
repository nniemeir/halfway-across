#ifndef AUDIO_H
#define AUDIO_H
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QUrl>
class Audio
{
public:
  Audio();
  void play(QString filePath, int volume, int isBackground);
  float getdefAmbienceVol() const;
  float getdefMusicVol() const;
  float getdefSfxVol() const;

private:
  float defAmbienceVol;
  float defMusicVol;
  float defSfxVol;
  QMediaPlayer *music;
  QAudioOutput *audioOutput;
};

extern Audio ambiencePlayer;
extern Audio musicPlayer;
extern Audio sfxPlayer;

#endif

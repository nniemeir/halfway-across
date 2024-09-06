#ifndef AUDIO_H
#define AUDIO_H
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QUrl>
class audio {
public:
  audio();
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

extern audio ambiencePlayer;
extern audio musicPlayer;
extern audio sfxPlayer;

#endif // AUDIO_H

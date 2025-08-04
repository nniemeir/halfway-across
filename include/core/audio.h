#ifndef AUDIO_H
#define AUDIO_H
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QUrl>

// Handles audio playback through its QMediaPlayer and QAudioOutput objects
class Audio {
public:
  Audio();

  // Getters
  float getAmbienceVol() const;
  float getMusicVol() const;
  float getSfxVol() const;
  
  void play(QString filePath, int volume, bool isBackground);

private:
  float ambienceVol;
  float musicVol;
  float sfxVol;
  QAudioOutput *audioOutput;
  QMediaPlayer *music;
};

#endif

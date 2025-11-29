#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <string>

class SoundManager {
private:
    sf::SoundBuffer buttonClickBuffer;
    sf::Sound buttonClickSound;
    sf::Music backgroundMusic;

public:
    SoundManager();
    ~SoundManager();

    bool loadButtonClickSound(const std::string& filename);
    void playButtonClick();

    bool loadBackgroundMusic(const std::string& filename);
    void playBackgroundMusic();
    void pauseBackgroundMusic();
    void stopBackgroundMusic();
    void setMusicVolume(float volume);
};

#endif

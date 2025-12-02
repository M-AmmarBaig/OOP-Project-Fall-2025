#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <string>

class SoundManager {
private:
    sf::SoundBuffer buttonClickBuffer;
    sf::Sound buttonClickSound;
    
    sf::SoundBuffer scoreBuffer;
    sf::Sound scoreSound;
    
    sf::SoundBuffer penaltyBuffer;
    sf::Sound penaltySound;
    
    sf::Music backgroundMusic;

public:
    SoundManager();
    ~SoundManager();

    bool loadButtonClickSound(const std::string& filename);
    void playButtonClick();

    bool loadScoreSound(const std::string& filename);
    void playScoreSound();

    bool loadPenaltySound(const std::string& filename);
    void playPenaltySound();

    bool loadBackgroundMusic(const std::string& filename);
    void playBackgroundMusic();
};

#endif

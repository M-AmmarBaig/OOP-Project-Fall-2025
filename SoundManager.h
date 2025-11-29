#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <string>

class SoundManager {
private:
    sf::SoundBuffer buttonClickBuffer;
    sf::Sound buttonClickSound;

public:
    SoundManager();
    ~SoundManager();

    bool loadButtonClickSound(const std::string& filename);
    void playButtonClick();
};

#endif
